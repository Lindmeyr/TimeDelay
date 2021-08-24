/* main.c - Application main entry point */

/*
 * Copyright (c) 2017 Intel Corporation
 * Additional Copyright (c) 2018 Espressif Systems (Shanghai) PTE LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <string.h>


#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "hal/gpio_types.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "esp_system.h"
#include "StandardLib.h"


#define LOG_LOCAL_LEVEL ESP_LOG_INFO
#include "esp_log.h"

static const char *TAG = "impulse_switch";
static int I = 0;
static int Q1 = 0;
static int Q2 = 0;
static int Q3 = 0;
static int Q4 = 0;




static const gpio_num_t BUTTON_IO_NUM 	= gpio_num_t::GPIO_NUM_32;		// Pin 32.
#define GPIO_Q1 GPIO_NUM_19
#define GPIO_Q2 GPIO_NUM_23
#define GPIO_Q3 GPIO_NUM_33
#define GPIO_Q4 GPIO_NUM_25

TON TON1;
TON TON2;
TON TON3;
TON TON4;

/* Inside .cpp file, app_main function must be declared with C linkage */
extern "C" void app_main(void)
{



    ESP_LOGI(TAG, "Initializing...");

    /* Configure the IOMUX register for pad BLINK_GPIO (some pads are
       muxed to GPIO on reset already, but some default to other
       functions and need to be switched to GPIO. Consult the
       Technical Reference for a list of pads and their default
       functions.)
    */
    gpio_reset_pin(GPIO_Q1);
    gpio_reset_pin(GPIO_Q2);
    gpio_reset_pin(GPIO_Q3);
    gpio_reset_pin(GPIO_Q4);
    gpio_reset_pin(BUTTON_IO_NUM);
    /* Set the GPIO as a push/pull output */
    gpio_set_direction(GPIO_Q1, GPIO_MODE_OUTPUT);
    gpio_set_direction(GPIO_Q2, GPIO_MODE_OUTPUT);
    gpio_set_direction(GPIO_Q3, GPIO_MODE_OUTPUT);
    gpio_set_direction(GPIO_Q4, GPIO_MODE_OUTPUT);
    gpio_set_direction(BUTTON_IO_NUM, GPIO_MODE_INPUT);
    gpio_set_level(GPIO_Q1, Q1); //set to 0 at Reset.
    gpio_set_level(GPIO_Q2, Q2); //set to 0 at Reset.
    gpio_set_level(GPIO_Q3, Q3); //set to 0 at Reset.
    gpio_set_level(GPIO_Q4, Q4); //set to 0 at Reset.



    TON1.PT =  500;
    TON2.PT = 1000;
    TON3.PT = 1500;
    TON4.PT = 2000;

    while (true) {
    	I = !gpio_get_level(BUTTON_IO_NUM);

    	Q1 = TON1(I);
    	Q2 = TON2(I);
    	Q3 = TON3(I);
    	Q4 = TON4(I);

        gpio_set_level(GPIO_Q1, Q1);
        gpio_set_level(GPIO_Q2, Q2);
        gpio_set_level(GPIO_Q3, Q3);
        gpio_set_level(GPIO_Q4, Q4);
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}
