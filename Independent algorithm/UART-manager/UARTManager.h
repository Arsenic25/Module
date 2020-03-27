/*
 * UARTManager.h
 *
 *  Created on: 2020/3/26
 *      Author: Arsenic
 */

#ifndef UARTMANAGER_H_
#define UARTMANAGER_H_

#define TX_DATA_LENGTH 8
#define RX_DATA_LENGTH 8
const uint8_t HEADER_PACKET[] = {'s', 0xFF, 0x00, 0xAA};
const uint8_t STOP_PACKET = 'e';

typedef struct {
    uint8_t onCapture = 0;

    uint16_t dataPointer = 0;
    uint8_t headerPointer = 0;

    uint8_t headerDetector[4];

    uint8_t serializedRxData[4*RX_DATA_LENGTH];
    uint8_t serializedTxData[4*TX_DATA_LENGTH];
    
    float data[RX_DATA_LENGTH];    
}UARTManager_t;

void rxUpdate(UARTManager_t *manager, uint8_t d);
void rxUpdateN(UARTManager_t *manager, uint8_t *d, int n);

#endif /* UARTMANAGER_H_ */