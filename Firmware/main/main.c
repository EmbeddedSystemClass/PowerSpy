#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "esp_system.h"

#define LED_RED 	25
#define LED_GREEEN  26
#define LED_BLUE	27

void app_main(void) {

    gpio_pad_select_gpio(LED_RED);
    gpio_pad_select_gpio(LED_GREEEN);
    gpio_pad_select_gpio(LED_BLUE);

    gpio_set_direction(LED_RED, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED_GREEEN, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED_BLUE, GPIO_MODE_OUTPUT);

    while(1) {
        gpio_set_level(LED_BLUE, 0);
        vTaskDelay(1000 / portTICK_PERIOD_MS);

        gpio_set_level(LED_BLUE, 1);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
/*
        gpio_set_level(LED_GREEEN, 0);
		vTaskDelay(100 / portTICK_PERIOD_MS);
		gpio_set_level(LED_GREEEN, 1);
		vTaskDelay(100 / portTICK_PERIOD_MS);

		gpio_set_level(LED_BLUE, 0);
		vTaskDelay(100 / portTICK_PERIOD_MS);
		gpio_set_level(LED_BLUE, 1);
		vTaskDelay(100 / portTICK_PERIOD_MS);
		*/
    }
}
