/*
 * UARTManager.c
 *
 *  Created on: 2020/3/26
 *      Author: Arsenic
 */
#include "UARTManager.h"

uint8_t HEADER_PACKET[4] = {'s', 0xFF, 0x00, 0xAA};
uint8_t STOP_PACKET = 'e';


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
                	union { float f; uint8_t byte[4]; } t;
                	t.byte[0] = manager->serializedRxData[4*i + 0];
                	t.byte[1] = manager->serializedRxData[4*i + 1];
                	t.byte[2] = manager->serializedRxData[4*i + 2];
                	t.byte[3] = manager->serializedRxData[4*i + 3];
                	manager->rxData[i] = t.f;
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
	union { float f; uint8_t byte[4]; } t;

    for (int i = 0; i < 4; i++) {               //make header packet
        manager->serializedTxData[i] = HEADER_PACKET[i];
    }

    for (int i = 0; i < TX_DATA_LENGTH; i++) {      //make data packet
    	t.f = manager->txData[i];
    	manager->serializedTxData[4 + (4*i) + 0] = t.byte[0];
    	manager->serializedTxData[4 + (4*i) + 1] = t.byte[1];
    	manager->serializedTxData[4 + (4*i) + 2] = t.byte[2];
    	manager->serializedTxData[4 + (4*i) + 3] = t.byte[3];
    }

    //make stop packet
    manager->serializedTxData[4 + 4*TX_DATA_LENGTH] = STOP_PACKET;
}
