/*******************************************************************************
 * File Name    : main.c
 * Date         : 2018/04/11
 * Team Name    : Team "Fine Fettle"
 * Programmers  : Ramanpreet Kaur, Divya Singla and Simranjit Singh
 * Student ID   : 7775026, 7770753 and 7769318
 * Group Number : 4
 * Project      : Artik Network Enabled Weighing
 * Description  : Use of ARTIK 053 Embedded Evaluation Board along with a 1Kg
 *                load cell (Weight sensor) to create a network-enabled weight.
 *******************************************************************************/

/****************************************************************************
 *
 * Copyright 2016 Samsung Electronics All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied. See the License for the specific
 * language governing permissions and limitations under the License.
 *****************************************************************************/

// Header Files
#include <tinyara/config.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "wifi.h"
#include "keys.h"
#include <tinyara/gpio.h>
#include <tinyara/pwm.h>
#include <tinyara/analog/adc.h>
#include <tinyara/analog/ioctl.h>
#include <apps/netutils/dhcpc.h>
#include <apps/netutils/mqtt_api.h>
#include <apps/netutils/ntpclient.h>


/* NTP */
#define NTP_REFRESH_PERIOD  (60 * 60)            // Seconds
#define ARRAY_SIZE(a) (sizeof(a)/sizeof((a)[0]))

#define RED_ON_BOARD_LED 45
#define ADC_MAX_SAMPLES 1         //Changed from 4 ADC's to 1.
#define NET_DEVNAME "wl1"
#define DEFAULT_CLIENT_ID "123456789"
#define SERVER_ADDR "api.artik.cloud"                                    //"52.200.124.224"
#define DEVICE_ID "aec7f507f7be47dabefaa0d1d6739e02"                     //FIX
#define DEVICE_TOKEN "826b3a3889c74009b7998a77f2c8b058"                  // FIX
#define ACTION_TOPIC "/v1.1/actions/aec7f507f7be47dabefaa0d1d6739e02"    // FIX
#define MESSAGE_TOPIC "/v1.1/messages/aec7f507f7be47dabefaa0d1d6739e02"  //FIX


/********************************************************
 * Function Name : gpio_read
 * Parameters    : port - GPIO port number.
 * Description   : Read the value of the given gpio port.
*********************************************************/
int gpio_read(int port)
{
  char buf[4];
  char devpath[16];
  snprintf(devpath, 16, "/dev/gpio%d", port);
  int fd = open(devpath, O_RDWR);

  if (fd < 0)
  {
    printf("fd open fail\n");
    return -1;
  }

  if (read(fd, buf, sizeof(buf)) < 0)
  {
    printf("read error\n");
    return -1;
  }
  close(fd);

  return buf[0] == '1';
}


/******************************************************
 * Function Name : gpio_write
 * Parameters    : port  - GPIO port number
 *                 value
 * Description   : Write the value of given gpio port.
 ******************************************************/
void gpio_write(int port, int value)
{
  char str[4];
  static char devpath[16];

  snprintf(devpath, 16, "/dev/gpio%d", port);
  int fd = open(devpath, O_RDWR);

  ioctl(fd, GPIOIOC_SET_DIRECTION, GPIO_DIRECTION_OUT);

  write(fd, str, snprintf(str, 4, "%d", value != 0) + 1);
  value=0;
  write(fd, str, snprintf(str, 4, "%d", value != 0) + 1);

  close(fd);
}


/******************************************************************************
 * Function Name : main
 * Parameters    : argc  - Number of command line arguments
 *                 *argv - Array of strings representing command
 *                         line arguments.
 * Description   : Reading HX711 GPIO port. In this, shift bits
 *                 left by 1 position and calibrating sensor by setting
 *                 scaling factor and displaying Analog to Digital Converted
 *                 (ADC) value on the console.
 ******************************************************************************/
int main(int argc, char *argv[])
{
  while (1)
    {
	  int ADC_Value;         // Declaring a variable to store the digital value.
      ADC_Value = 0;
      int temp;              // Declaring a temp variable.
      temp = 16777215;

      // Read HX711 GPIO port
      int j;

      for ( j = 1; j <= 25; j++)       // Read in 24 bit ADC plus one
      {
    	  /***************************************************
    	   if condition runs until j variable is less than 25
    	  ****************************************************/
        if (j < 25)
		{
			gpio_write(53,1);                       // Clock pulse

			ADC_Value = ADC_Value << 1;             // Shift bits left by 1 position
			ADC_Value = ADC_Value | gpio_read(32);  // OR ADC data bit to LSB
		}

        else
        	gpio_write(53,1);       // Clock pulse

      }

      ADC_Value = temp - ADC_Value;
      ADC_Value = ADC_Value - 174000;                         // Calibrating sensor by setting Zero offset
      ADC_Value = ADC_Value / 2200;                           // Calibrating sensor by Scaling to grams
      printf("HX711 read value is %d grams\n", ADC_Value);    // Displaying Weight of the load on the console.

      sleep(3);             // Giving delay of 3 milliseconds.
      ADC_Value = 0;        // Reseting ADC value to 0.
     }

  return 0;
}
