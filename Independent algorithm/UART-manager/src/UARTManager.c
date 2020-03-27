/*
 * UARTManager.c
 *
 *  Created on: 2020/3/26
 *      Author: Arsenic
 */
#include "UARTManager.h"

void initUARTManager(UARTManager_t *manager) {
    manager->onCapture = 0;
    manager->dataPointer = 0;
    manager->headerPointer = 0;
}

void rxUpdate(UARTManager_t *manager, uint8_t d) {
    if (!(manager->onCapture)) {    // try detect header packet
        manager->headerDetector[manager->headerPointer] = d;

        if (    //check header packet
            (manager->headerDetector[((manager->headerPointer) + 1)%4] == HEADER_PACKET[0]) &&
            (manager->headerDetector[((manager->headerPointer) + 2)%4] == HEADER_PACKET[1]) &&
            (manager->headerDetector[((manager->headerPointer) + 3)%4] == HEADER_PACKET[2]) &&
            (manager->headerDetector[((manager->headerPointer) + 0)%4] == HEADER_PACKET[3])
        ) {     //start capture
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
                    manager->rxData[i] = (float)(
                        (manager->serializedRxData[4*i + 0] << 24) |
                        (manager->serializedRxData[4*i + 1] << 16) |
                        (manager->serializedRxData[4*i + 2] << 8) |
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

void makeTxData(UARTManager_t *manager) {
    for (int i = 0; i < 4; i++) {               //make header packet
        manager->serializedTxData[i] = HEADER_PACKET[i];
    }

    for (int i; i < TX_DATA_LENGTH; i++) {      //make data packet
        manager->serializedTxData[4 + (4*i) + 0] = (uint8_t)((manager->txData[i] & 0xFF000000) >> 24);
        manager->serializedTxData[4 + (4*i) + 1] = (uint8_t)((manager->txData[i] & 0x00FF0000) >> 16);
        manager->serializedTxData[4 + (4*i) + 2] = (uint8_t)((manager->txData[i] & 0x0000FF00) >> 8);
        manager->serializedTxData[4 + (4*i) + 3] = (uint8_t)((manager->txData[i] & 0x000000FF) >> 0);
    }

    //make stop packet
    manager->serializedTxData[4 + 4*TX_DATA_LENGTH] = STOP_PACKET;
}
