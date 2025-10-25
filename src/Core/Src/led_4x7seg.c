#include "led_4x7seg.h"

// Variables
static uint8_t current_scan_position = 0; // Current scanning position for multiplexing

static SPI_HandleTypeDef* hspi_led_7seg = NULL; // SPI handle for 7-segment display

static int8_t spi_transmit_buffer[SPI_TRANSMIT_BUFFER_SIZE] = {
    0xFF, 
    0xFF
}; // SPI buffer for data transmission

static int8_t led_7seg_display_value[4] = {
    LED_7SEG_ALL_ON, 
    LED_7SEG_ALL_ON, 
    LED_7SEG_ALL_ON, 
    LED_7SEG_ALL_ON
}; // Buffer to hold the display values for 4 7 segment leds

static const uint8_t led_7seg_value_map[12] = {
    LED_7SEG_NUM0,
    LED_7SEG_NUM1,
    LED_7SEG_NUM2,
    LED_7SEG_NUM3,
    LED_7SEG_NUM4,
    LED_7SEG_NUM5,
    LED_7SEG_NUM6,
    LED_7SEG_NUM7,
    LED_7SEG_NUM8,
    LED_7SEG_NUM9,
    LED_7SEG_CLEAR,
    LED_7SEG_ALL_ON
}; // Map value numbers 0-9, CLEAR, ALL_ON for 7 segments led

// Private Functions Definition
static int8_t led_7seg_updateDisplay(){

    HAL_GPIO_WritePin(LD_LATCH_GPIO_Port, LD_LATCH_Pin, GPIO_PIN_RESET);
    HAL_SPI_Transmit(hspi_led_7seg, (uint8_t*)spi_transmit_buffer, SPI_TRANSMIT_BUFFER_SIZE, HAL_MAX_DELAY);
    HAL_GPIO_WritePin(LD_LATCH_GPIO_Port, LD_LATCH_Pin, GPIO_PIN_SET);

    return 0;
}

// Global Functions Definition
int8_t led_7seg_init(SPI_HandleTypeDef* hspi){
    if(hspi == NULL){
        return -1;
    }

    hspi_led_7seg = hspi;

    led_7seg_test();

    return 0;
}

int8_t led_7seg_setNumber(uint8_t position, uint8_t number){
    if( position < 0 || position > 3){
        return -1;
    }
    if (number > 11) {
        return -1;
    }

    led_7seg_display_value[position] = led_7seg_value_map[number];
    return 0;
}

int8_t led_7seg_getDisplayValue(uint8_t position){
    if( position < 0 || position > 3){
        return -1;
    }

    return led_7seg_display_value[position];
}

int8_t led_7seg_setDot(uint8_t position, uint8_t state){
    if( position < 0 || position > 3){
        return -1;
    }

    if(state == 1){
        led_7seg_display_value[position] &= 0x7F; // Set dot segment ON
    } else {
        led_7seg_display_value[position] |= 0x80; // Set dot segment OFF
    }

    return 0;
}

int8_t led_7seg_getDotState(uint8_t position){
    if( position < 0 || position > 3){
        return -1;
    }
    if(led_7seg_display_value[position] >> 7){
        return 0; // Dot is OFF
    } else {
        return 1; // Dot is ON
    }
}

void led_7seg_scan(void){
    spi_transmit_buffer[0] = 0xFF;
    spi_transmit_buffer[1] = 0xFF;
    switch (current_scan_position)
    {
    case 0:
        spi_transmit_buffer[0] = 0xB0;
        spi_transmit_buffer[1] = led_7seg_display_value[0];
        break;
    case 1:
        spi_transmit_buffer[0] = 0xD0;
        spi_transmit_buffer[1] = led_7seg_display_value[1];
        break;
    case 2:
        spi_transmit_buffer[0] = 0xE0;
        spi_transmit_buffer[1] = led_7seg_display_value[2];
        break;
    case 3:
        spi_transmit_buffer[0] = 0x70;
        spi_transmit_buffer[1] = led_7seg_display_value[3];
        break;
    }
    current_scan_position = (current_scan_position + 1) % 4;

    led_7seg_updateDisplay();
}

int8_t led_7seg_test(void){
    led_7seg_turnOnAll();
    HAL_Delay(500);
    led_7seg_turnOffAll();
    HAL_Delay(500);
    led_7seg_turnOnAll();
    HAL_Delay(500);
    led_7seg_turnOffAll();
    HAL_Delay(500);
    led_7seg_turnOnAll();
    HAL_Delay(500);
    led_7seg_turnOffAll();
    return 0;
}

void led_7seg_turnOffAll(void){
    spi_transmit_buffer[0] = 0xFF;
    spi_transmit_buffer[1] = 0x00;

    led_7seg_updateDisplay();
}

void led_7seg_turnOnAll(void){
    spi_transmit_buffer[0] = 0x00;
    spi_transmit_buffer[1] = 0xFF;

    led_7seg_updateDisplay();
}
