// Copyright (c) 2011, XMOS Ltd, All rights reserved
// This software is freely distributable under a derivative of the
// University of Illinois/NCSA Open Source License posted in
// LICENSE.txt and at <http://github.xcore.com/>

#ifndef APP_HANDLER_H_
#define APP_HANDLER_H_
#include "i2c.h"

typedef struct gpio_state {
  int valve_1;
  int valve_2;
  int led_0;
  int led_1;
  int led_2;
  int led_3;
} gpio_state_t;

/** =========================================================================
 * app_handler
 *
 * Implements GPIO button press checks, reads onboard ADC temperature value,
 * handles GPIO web commands to set/reset LEDs, read tempearture and button
 * statuses
 *
 * \param c_gpio channel to communicate gpio data between app handler and
 * tcp handler
 * \param p_led GPIO LED ports
 * \param p_valve valve ports
 * \return None
 *
 **/
void app_handler(chanend c_gpio, port p_led, port p_valve1,port p_valve2, port p_valve3);
void set_gpio_state(chanend c_gpio, REFERENCE_PARAM(gpio_state_t, gpio_new_state));
void get_gpio_state(chanend c_gpio, REFERENCE_PARAM(gpio_state_t, gpio_state));

#endif /* APP_HANDLER_H_ */
