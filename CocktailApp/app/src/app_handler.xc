// Copyright (c) 2011, XMOS Ltd, All rights reserved
// This software is freely distributable under a derivative of the
// University of Illinois/NCSA Open Source License posted in
// LICENSE.txt and at <http://github.xcore.com/>

#include "app_handler.h"
#include "profile.h"
#include <profile_control.h>
#include <dc_motor_config.h>
#include <print.h>

#include <xccompat.h>


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



void app_handler(chanend c_position_ctrl, chanend c_gpio, port p_valve1, port p_valve2, port p_valve3, port p_valve4) {
	unsigned time;

	  while (1) {
	    select {
	      case c_gpio :> int cmd:
	        switch (cmd) {
	          case APP_HANDLER_SET_GPIO_STATE: {
	        	  timer tmr;
				  unsigned isOn = 0;
				  unsigned t;
				  int ON_PERIOD = 1000000000;
				  int DELAY_PERIOD = 1000000000;

				  //motor control stuff
				  int target_position = 30;			// degree
				  int velocity 		= 100;			// rpm
				  int acceleration 	= 150;			// rpm/s
				  int deceleration 	= 150;     		// rpm/s


	        	gpio_state_t gpio_new_state;
	        	init_position_profile_limits(GEAR_RATIO, MAX_ACCELERATION, MAX_PROFILE_VELOCITY);
	        	c_gpio :> gpio_new_state;
	        	tmr :> t;

	        	printstrln("Option 1 is \n");
	        	printintln(gpio_new_state.led_0);
	        	printstrln("Option 2 is \n");
	            printintln(gpio_new_state.led_1);
	        	printstrln("Option 3 is \n");
	        	printintln(gpio_new_state.led_2);
	        	printstrln("Option 4 is \n");
	            printintln(gpio_new_state.led_3);

	        	if(gpio_new_state.led_0)
	        	{
	        		printstrln("drink 1 is selected!");
	        		/* //valve 1 operates
					  p_valve1 <: isOn;
					  t += ON_PERIOD;
					  tmr when timerafter (t) :> void;
					  p_valve1 <: !isOn;

					  set_profile_position(target_position, velocity, acceleration, deceleration, c_position_ctrl);

					  //delay for the bottle on the conveyor to move to the next valve
					  t += DELAY_PERIOD;
					  tmr when timerafter (t) :> void;

					  //valve 2 operates
					  p_valve2 <: isOn;
					  t += ON_PERIOD;
					  tmr when timerafter (t) :> void;
					  p_valve2 <: !isOn;

					  target_position += 30;			// degree
					  set_profile_position(target_position, velocity, acceleration, deceleration, c_position_ctrl);

					  //delay for the bottle on the conveyor to move to the next valve
					  t += DELAY_PERIOD;
					  tmr when timerafter (t) :> void;

					  //valve 3 operates
					  p_valve3 <: isOn;
					  t += ON_PERIOD;
					  tmr when timerafter (t) :> void;
					  p_valve3 <: !isOn;

					  target_position += 30;			// degree
					  set_profile_position(target_position, velocity, acceleration, deceleration, c_position_ctrl);

					  //delay for the bottle on the conveyor to move to the next valve
					  t += DELAY_PERIOD;
					  tmr when timerafter (t) :> void;

					  //valve 4 operates
					  p_valve4 <: isOn;
					  t += ON_PERIOD;
					  tmr when timerafter (t) :> void;
					  p_valve4 <: !isOn;

					  printstr("Your drink is ready! Enjoy it!! \n\n\n");*/
	        	}

	        	if(gpio_new_state.led_1){
	        		printstrln("drink 2 is selected!");
	        	}
	        	if(gpio_new_state.led_2){
					printstrln("drink 3 is selected!");
				}
	        	if(gpio_new_state.led_3){
					printstrln("drink 4 is selected!");
				}


	        	gpio_state.led_0 = gpio_new_state.led_0;
	        	gpio_state.led_1 = gpio_new_state.led_1;
	        	gpio_state.led_2 = gpio_new_state.led_2;
	        	gpio_state.led_3 = gpio_new_state.led_3;
	          }
	          break;
	          case APP_HANDLER_GET_GPIO_STATE: {
	           c_gpio <: gpio_state;
	          }
	          break;
	        } //switch (cmd)
	      break; //case c_gpio :> int cmd:
	    } //select
	  } //while (1)
}
