/*
 * UARTManager.c
 *
 *  Created on: 2020/3/26
 *      Author: Arsenic
 */
#include "UARTManager.h"

void rxUpdate(UARTManager_t *manager, uint8_t d) {
    if (!(manager->onCapture)) {    // try detect header packet
        manager->headerDetector[manager->headerPointer] = d;

        if (    //check header packet
            (manager->headerDetector[((manager->headerPointer)+1)%4] == HEADER_PACKET[0]) &&
            (manager->headerDetector[((manager->headerPointer)+2)%4] == HEADER_PACKET[1]) &&
            (manager->headerDetector[((manager->headerPointer)+3)%4] == HEADER_PACKET[2]) &&
            (manager->headerDetector[((manager->headerPointer))%4] == HEADER_PACKET[3])
        ) {     //stert capture
            manager->onCapture = 1;
            manager->dataPointer = 0;
        }

        manager->headerPointer++;
        if (4 <= manager->headerPointer) manager->headerPointer = 0;

    } else {    // capture data for RX_DATA_LENGTH times and check stop packet
        if (4*RX_DATA_LENGTH <= manager->dataPointer) {     //check stop packet and right then save receive data
            manager->onCapture = 0;
            manager->dataPointer = 0;

            if (d == STOP_PACKET) {     //save available rx data
                for (int i = 0; i < RX_DATA_LENGTH; i++) {
                    manager->data[i] = (float)(
                        manager->serializedRxData[4*i] |
                        manager->serializedRxData[4*i + 1] |
                        manager->serializedRxData[4*i + 2] |
                        manager->serializedRxData[4*i + 3]
                    );
                }
            }
            
        } else {
            manager->serializedRxData[manager->dataPointer] = d;
            manager->dataPointer++;
        }
    }
}

void rxUpdateN(UARTManager_t *manager, uint8_t *d, int n) {
    for (int i = 0; i < n; i++) {
        rxUpdate(manager, d[i]);
    }
}

