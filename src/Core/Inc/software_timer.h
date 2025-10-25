#ifndef __SOFTWARE_TIMER_H__
#define __SOFTWARE_TIMER_H__

// Essential libraries
#include "stdint.h"
#include "main.h"

// Macros
#define NUMBER_OF_TIMERS 14 // Total of 14 TIM in STM32F4xx
#define SW_TIMER2 2
//.........

#define NUMBER_OF_SW_TIMER2 1

#define TIM2_INTERVAL 1 // in ms

/**
 * @brief
 * Software Timer Structure
 */
typedef struct {
    uint8_t timer_flag;
    uint32_t timer_counter;
    uint32_t duration;
    int32_t repetition;
} SoftwareTimer;

/**
 * @brief
 * Function: initSoftwareTimer
 * @param htim: Pointer to TIM handle
 * @return 0 on success, -1 on error
*/
extern int8_t initSoftwareTimer(TIM_HandleTypeDef* htim);

/**
 * @brief
 * Function: getFlag
 * @param timer: Timer number (from 1 to 14)
 * @param sw_timer_index: Pointer to software timer index
 * @return Timer flag status (0: not set, 1: set), -1 on error
*/
extern int8_t getFlag(uint8_t timer, uint32_t* sw_timer_index);

/**
 * @brief
 * Function: resetFlag
 * @param timer: Timer number (from 1 to 14)
 * @param sw_timer_index: Pointer to software timer index
 * @return 0 on success, -1 on error
*/
extern int8_t resetFlag(uint8_t timer, uint32_t* sw_timer_index);

/**
 * @brief
 * Function: setTimer
 * @param timer: Timer number (from 1 to 14)
 * @param duration: Pointer to duration value
 * @param repetition: Pointer to repetition value (-1 for infinite)
 * @param sw_timer_index: Pointer to software timer index
 * @return 0 on success, -1 on error
*/
extern int8_t setTimer(uint8_t timer, uint32_t* duration, int32_t* repetition, uint32_t* sw_timer_index);

/**
 * @brief
 * Function: setRepetition
 * @param timer: Timer number (from 1 to 14)
 * @param repetition: Pointer to repetition value (-1 for infinite)
 * @param sw_timer_index: Pointer to software timer index
 * @return 0 on success, -1 on error
*/
extern int8_t setRepetition(uint8_t timer, int32_t* repetition, uint32_t* sw_timer_index);

#endif /* __SOFTWARE_TIMER_H__ */