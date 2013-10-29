// Copyright (c) 2011, XMOS Ltd, All rights reserved
// This software is freely distributable under a derivative of the
// University of Illinois/NCSA Open Source License posted in
// LICENSE.txt and at <http://github.xcore.com/>

#include "app_handler.h"
#include <xccompat.h>
#include <print.h>

#define I2C_NO_REGISTER_ADDRESS	1
#define DEBOUNCE_INTERVAL	XS1_TIMER_HZ/50
#define BUTTON_1_PRESS_VALUE	0x2

typedef enum gpio_cmd_t {
  APP_HANDLER_SET_GPIO_STATE,
  APP_HANDLER_GET_GPIO_STATE,
} gpio_cmd_t;

gpio_state_t gpio_state;

void set_gpio_state(chanend c_gpio, gpio_state_t &data)
{
  printstrln("setting gpio state");
  c_gpio <: APP_HANDLER_SET_GPIO_STATE;
  c_gpio <: data;
}

void get_gpio_state(chanend c_gpio, gpio_state_t &data)
{
  c_gpio <: APP_HANDLER_GET_GPIO_STATE;
  c_gpio :> data;
}

// Read ADC value using I2C
static int read_adc_value(r_i2c &p_i2c)
{
  return 0;
}

void app_handler(chanend c_gpio, port p_led, port p_valve1,port p_valve2, port p_valve3) {
  while (1) {
    select {
      case c_gpio :> int cmd:
        switch (cmd) {
          case APP_HANDLER_SET_GPIO_STATE: {
        	gpio_state_t gpio_new_state;
        	unsigned int valve1_state = 0; //valve off
        	p_valve1:> valve1_state;
        	c_gpio :> gpio_new_state;

        	gpio_state.led_0 = gpio_new_state.led_0;
        	gpio_state.led_1 = gpio_new_state.led_1;
        	gpio_state.led_2 = gpio_new_state.led_2;
        	gpio_state.led_3 = gpio_new_state.led_3;
        	gpio_state.valve_1 = gpio_new_state.valve_1;
        	printstrln("gonna set the gpio state now to....");
        	printintln(valve1_state);
        	p_valve1 <: gpio_state.led_0;
        	p_valve2 <: gpio_state.led_1;
        	p_valve3 <: gpio_state.led_2;
          }
          break;
          case APP_HANDLER_GET_GPIO_STATE: {
            /* Button states are already updated */
            c_gpio <: gpio_state;
          }
          break;
        } //switch (cmd)
      break;
    }
  } //while (1)
}
