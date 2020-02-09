/* 			LIBRARIES DECLARATION 			*/
#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_system.h"
#include "sdkconfig.h"
#include "esp_log.h"

#include "driver/gpio.h"

#include <ads111x.h>
#include <string.h>


/* 			HARDWARE PINS DEFINITIONS 			*/

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

#define DEV_COUNT 1

#define I2C_PORT 0


#define SDA_GPIO 21
#define SCL_GPIO 22


#define GAIN ADS111X_GAIN_4V096 // +-4.096V

// I2C addresses
static const uint8_t addr[DEV_COUNT] = {
    ADS111X_ADDR_GND,

};

// Descriptors
static i2c_dev_t devices[DEV_COUNT];

// Gain value
static float gain_val;


// Main task
void ads111x_test(void *pvParamters)
{
    gain_val = ads111x_gain_values[GAIN];

    // Setup ICs
	ESP_ERROR_CHECK(ads111x_init_desc(&devices[0], addr[0], I2C_PORT, SDA_GPIO, SCL_GPIO));

	ESP_ERROR_CHECK(ads111x_set_mode(&devices[0], ADS111X_MODE_CONTUNOUS));    // Continuous conversion mode
	ESP_ERROR_CHECK(ads111x_set_data_rate(&devices[0], ADS111X_DATA_RATE_32)); // 32 samples per second
	ESP_ERROR_CHECK(ads111x_set_input_mux(&devices[0], ADS111X_MUX_1_GND));    // positive = AIN0, negative = GND
	ESP_ERROR_CHECK(ads111x_set_gain(&devices[0], GAIN));


    while (1)
    {
	   // wait for conversion end
		bool busy;
		do
		{
			ads111x_is_busy(&devices[0], &busy);
		}
		while (busy);

		// Read result
		int16_t raw = 0;
		if (ads111x_get_value(&devices[0], &raw) == ESP_OK)
		{
			float voltage = gain_val / ADS111X_MAX_VALUE * raw;
			printf("[%u] Raw ADC value: %d, voltage: %.04f volts\n", 0, raw, voltage);
		}
		else
			printf("[%u] Cannot read ADC value\n", 0);



        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}

void app_main()
{
    // Init library
    ESP_ERROR_CHECK(i2cdev_init());

    // Clear device descriptors
    memset(devices, 0, sizeof(devices));

    // Start task
    xTaskCreatePinnedToCore(&ads111x_test, "ads111x_test", configMINIMAL_STACK_SIZE * 8, NULL, 5, NULL, PRO_CPU_NUM);
}

