# timer-and-interrupt
## Overview
A simple Timer and Timer interrupt project from the Embedded Systems lab (CO3053), HCMUT.

This project is written for STM32F407ZGT6.

## Software Timer
### Enable Timer and Configure Timer
Include `software_timer.h` to use software timer.

Please add the following definitions to `software_timer.h` to use timer:
+ Add `#define SW_TIMERx` with x is your timer (ranges from 1 to 14).
+ Add `#define NUMBER_OF_SW_TIMERx y` with x is your timer (ranges from 1 to 14), y is the number of software timer your created using timer x.
+ Add `#define TIMx_INTERVAL y` with x is your timer (ranges from 1 to 14), y is the interval in ms of that timer.

Example:
+ Using TIM2; 
+ Clock Source: Internal; 
+ APB1 Timer clocks: 84(MHz); 
+ Prescaler: 840-1; 
+ Counter Period: 100-1
    - Interval of TIM2: $ \frac{84000000}{(840-1+1).(100-1+1)} = 1000 (Hz) \Rightarrow 1 (ms)$
```
// software_timer.h

#define SW_TIMER2             // Using timer 2 for software timer
#define NUMBER_OF_SW_TIMER2 3 // There are 3 software timers for timer 2
#define TIM2_INTERVAL       1 // The interval of TIM2 is calculated above (ms)
```

### Using Software Timer
The software timer module exposes the following functions. Signatures are in `software_timer.h`.

+ `int8_t initSoftwareTimer(TIM_HandleTypeDef* htim);`
    - Start the HAL timer interrupt for the given `htim`. Call this once for each enabled hardware timer (e.g., in `main()` after HAL timer init).
    - Returns 0 on success, -1 on fail

+ `int8_t getFlag(uint8_t timer, uint32_t* sw_timer_index);`
    - Returns the `timer_flag` for the software timer identified by `timer` (which should be `SW_TIMERx`) and `*sw_timer_index` (0-based index into that SW_TIMERx's array).
    - Return value is the flag (0 for not raise, 1 for raise). If arguments are invalid it returns a sentinel value (-1).

+ `int8_t resetFlag(uint8_t timer, uint32_t* sw_timer_index);`
    - Clears the expiration flag for that software timer (implementation detail: resets `timer_flag` to 0).
    - Returns 0 on success, -1 on fail

+ `int8_t setTimer(uint8_t timer, uint32_t* duration, uint32_t* sw_timer_index);`
    - Set the duration (in ticks of `TIMx_INTERVAL`) for the software timer at the given index. 
    - Returns 0 on success, -1 on fail

+ `int8_t setRepetition(uint8_t timer, int32_t* repetition, uint32_t* sw_timer_index);`
    - If supported, set the repetition count (how many times the timer should auto-restart).
    - Returns 0 on sucess, -1 on fail

## 7 Segments Clock LED Clock
### Basic structure
The 7 segments Clock LED (C93) is controlled by STM32F407ZGT6 through 2 ICs 74HC595 (using SPI protocol), take a look at the schematic below:
```
                                        ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
                                        ┃                                        ┃
              ┏━━━━┳┳━━━━┓              ┃              ┏━━━━┳┳━━━━┓              ┃
          X ━━┫1   ╰╯  16┣━━ VCC        ┃  CLOCK LED ━━┫1   ╰╯  16┣━━ VCC        ┃
          X ━━┫2       15┣━━ X          ┃  CLOCK LED ━━┫2       15┣━━ CLOCK LED  ┃
          X ━━┫3   74  14┣━━ ━━━━━━━━━━━┛  CLOCK LED ━━┫3   74  14┣━━ PB5(STM32) ┃
      DIG.3 ━━┫4   HC  13┣━━ GND           CLOCK LED ━━┫4   HC  13┣━━ GND        ┃
      DIG.2 ━━┫5  595  12┣━━ PG6 (STM32)   CLOCK LED ━━┫5  595  12┣━━ PG6(STM32) ┃
      DIG.1 ━━┫6       11┣━━ PB3 (STM32)   CLOCK LED ━━┫6       11┣━━ PB3(STM32) ┃
      DIG.4 ━━┫7       10┣━━ VCC           CLOCK LED ━━┫7       10┣━━ VCC        ┃
         GND━━┫8        9┣━━ X                    GND━━┫8        9┣━━ ━━━━━━━━━━━┛
              ┗━━━━━━━━━━┛                             ┗━━━━━━━━━━┛              
```
`DIG.x (with x from 1 to 4): toggle the specified 7 segments Led`
`CLOCK LED: toggle specified Led in 7 segments Led`
`PB5 Pin: Sends signals to the 74hc595 to control Led`