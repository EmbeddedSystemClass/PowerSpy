#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "esp_system.h"

/* HARDWARE PINS DEFINITIONS */

//User's Interface
#define LED_RED_PIN 			25
#define LED_GREEEN_PIN  		26
#define LED_BLUE_PIN			27
#define BUTTON_PROG_PIN			23

//Analog Front-End Interface
#define ADC_CURRENT_L1_PIN 		32
#define ADC_CURRENT_L2_PIN 		33
#define ADC_VOLTAGE_L1_PIN 		34
#define ADC_VOLTAGE_L2_PIN 		35

#define ADC_TO_I2C_ALERT		19
#define ADC_TO_I2C_SDA			21
#define ADC_TO_I2C_SCL			22

int color_led = 0;
int debounce = 0;


void app_main(void) {

    gpio_pad_select_gpio(LED_RED_PIN);
    gpio_pad_select_gpio(LED_GREEEN_PIN);
    gpio_pad_select_gpio(LED_BLUE_PIN);
    gpio_pad_select_gpio(BUTTON_PROG_PIN);

    gpio_set_direction(LED_RED_PIN,    GPIO_MODE_OUTPUT);
    gpio_set_direction(LED_GREEEN_PIN, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED_BLUE_PIN,   GPIO_MODE_OUTPUT);
    gpio_set_direction(BUTTON_PROG_PIN, GPIO_MODE_INPUT);

    gpio_set_level(LED_RED_PIN, 0);
    gpio_set_level(LED_GREEEN_PIN, 0);
    gpio_set_level(LED_BLUE_PIN, 0);

    printf("Hello world!\n");

    while(1) {


    	if(!gpio_get_level(BUTTON_PROG_PIN))
    	{
    		debounce = 0;

    		while(!gpio_get_level(BUTTON_PROG_PIN)) {
    			debounce++;
    		}

    		if (debounce >= 500)
    			color_led++;

    		printf("Color: %d\n", color_led);
    	}

    	if(color_led == 0)      { gpio_set_level(LED_RED_PIN, 1); gpio_set_level(LED_GREEEN_PIN, 0); gpio_set_level(LED_BLUE_PIN, 0); }
    	else if(color_led == 1) { gpio_set_level(LED_RED_PIN, 0); gpio_set_level(LED_GREEEN_PIN, 1); gpio_set_level(LED_BLUE_PIN, 0); }
    	else if(color_led == 2) { gpio_set_level(LED_RED_PIN, 0); gpio_set_level(LED_GREEEN_PIN, 0); gpio_set_level(LED_BLUE_PIN, 1); }
    	else color_led = 0;
    }
}
