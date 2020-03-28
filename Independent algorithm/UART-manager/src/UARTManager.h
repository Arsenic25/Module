/*
 * UARTManager.h
 *
 *  Created on: 2020/3/26
 *      Author: Arsenic
 */

#ifndef UARTMANAGER_H_
#define UARTMANAGER_H_

#include <stdint.h>

#define TX_DATA_LENGTH 5
#define RX_DATA_LENGTH 5
extern uint8_t HEADER_PACKET[4];
extern uint8_t STOP_PACKET;

typedef struct {
    uint8_t onCapture;

    uint16_t dataPointer;
    uint8_t headerPointer;

    uint8_t headerDetector[4];

    uint8_t serializedRxData[4*RX_DATA_LENGTH];
    uint8_t serializedTxData[4 + 4*TX_DATA_LENGTH + 1];

    float rxData[RX_DATA_LENGTH];
    float txData[TX_DATA_LENGTH];

} UARTManager_t;

void initUARTManager(UARTManager_t *manager);

void rxUpdate(UARTManager_t *manager, uint8_t d);
void rxUpdateN(UARTManager_t *manager, uint8_t *d, int n);

void makeTxData(UARTManager_t *manager);

#endif /* UARTMANAGER_H_ */
