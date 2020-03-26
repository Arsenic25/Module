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

typedef struct {
    uint8_t headerDetector[4];
    uint8_t serializedRxData[4*RX_DATA_LENGTH];
    uint8_t serializedTxData[4*TX_DATA_LENGTH];
    float rxData[RX_DATA_LENGTH];
    int dataPointer = 0;

}UARTManager_t;

#endif /* UARTMANAGER_H_ */