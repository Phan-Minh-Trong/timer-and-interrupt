#ifndef INC_LED_7SEG_H_
#define INC_LED_7SEG_H_

// Essential libraries
#include "stdint.h"
#include "main.h"

// Macros
#define LED_7SEG_NUM0   (uint8_t)0x03
#define LED_7SEG_NUM1   (uint8_t)0x9F
#define LED_7SEG_NUM2   (uint8_t)0x25
#define LED_7SEG_NUM3   (uint8_t)0x0D
#define LED_7SEG_NUM4   (uint8_t)0x99
#define LED_7SEG_NUM5   (uint8_t)0x49
#define LED_7SEG_NUM6   (uint8_t)0x41
#define LED_7SEG_NUM7   (uint8_t)0x1F
#define LED_7SEG_NUM8   (uint8_t)0x01
#define LED_7SEG_NUM9   (uint8_t)0x09
#define LED_7SEG_CLEAR  (uint8_t)0xFF
#define LED_7SEG_ALL_ON (uint8_t)0x00

#define SPI_TRANSMIT_BUFFER_SIZE 2

/**
 * @brief
 * Function: led_7seg_init
 * @param hspi: Pointer to SPI handle
 * @return 0 on success, -1 on error
 */
int8_t led_7seg_init(SPI_HandleTypeDef* hspi);

/**
 * @brief
 * Function: led_7seg_setNumber
 * @param position: Position of the 7-segment display (0-3)
 * @param number: Number to display (0-9), 
 *                or use LED_7SEG_CLEAR to turn off,
 *                or LED_7SEG_ALL_ON to turn on all segments.
 * @return 0 on success, -1 on error
 */
int8_t led_7seg_setNumber(uint8_t position, uint8_t number);

/**
 * @brief
 * Function: led_7seg_getDisplayValue
 * @param position: Position of the 7-segment display (0-3)
 * @return Current display value of the specified position
 */
int8_t led_7seg_getDisplayValue(uint8_t position);

/**
 * @brief
 * Function: led_7seg_setDot
 * @param position: Position of the 7-segment display (0-3)
 * @param state: State of the dot (0: off, 1: on)
 * @return 0 on success, -1 on error
 */
int8_t led_7seg_setDot(uint8_t position, uint8_t state);

/**
 * @brief
 * Function: led_7seg_getDotState
 * @param position: Position of the 7-segment display (0-3)
 * @return State of the dot (0: off, 1: on), -1 on error
 */
int8_t led_7seg_getDotState(uint8_t position);

/**
 * @brief
 * Function: led_7seg_scan
 * @param None
 */
void led_7seg_scan(void);

/**
 * @brief
 * Function: led_7seg_test
 * @param None
 */
int8_t led_7seg_test(void);

/**
 * @brief 
 * Function: led_7seg_turnOffAll
 * @param None
 */
void led_7seg_turnOffAll(void);

/**
 * @brief 
 * Function: led_7seg_turnOnAll
 * @param None
 */
void led_7seg_turnOnAll(void);


#endif /* INC_LED_7SEG_H_ */