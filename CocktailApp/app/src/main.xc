/*
 *
 * \file
 * \brief Main project file
 *
 * Port declarations, etc.
 *
 * \author Martin Schwarz <mschwarz@synapticon.com>
 * \version 0.1 (2012-11-23 1850)
 *
 */

#include <xs1.h>
#include <platform.h>
#include <print.h>
#include <stdio.h>
#include <stdint.h>
#include "ioports.h"
#include "hall_server.h"
#include "hall_client.h"
#include "qei_client.h"
#include "pwm_service_inv.h"
#include "comm_loop.h"
#include "refclk.h"
#include <xscope.h>
#include "qei_client.h"
#include "qei_server.h"
#include <dc_motor_config.h>
#include "profile.h"
#include <position_ctrl.h>
#include <drive_config.h>
#include <profile_control.h>
//#include <flash_somanet.h>
#include <internal_config.h>

//for the app thread
#include "app_handler.h"

//for wifi
#include "wifi_tiwisl_server.h"
#include "wifi_tiwisl_config.h"
#include "web_server.h"


#define p_valve1 p_ifm_ext_d0
#define p_valve2 p_ifm_ext_d1
#define p_valve3 p_ifm_ext_d2
#define p_valve4 p_ifm_ext_d3



/*
 * Wifi stuff
 */
#define DHCP
on stdcore[0]: out port ext_ant=XS1_PORT_1F; //(for Victor's module)

//::Ports Start
 on stdcore[0]: spi_master_interface tiwisl_spi =
 {
 XS1_CLKBLK_1,
 XS1_CLKBLK_2,
 XS1_PORT_1K, // MOSI
 XS1_PORT_1J, // CLK
 XS1_PORT_1I, // MISO
 };


 on stdcore[0]: wifi_tiwisl_ctrl_ports_t tiwisl_ctrl =
 {

 XS1_PORT_4E, // nCS - Bit0, Power enable - Bit1
 XS1_PORT_1L, // nIRQ
 };

 //on stdcore[3]: port p_valve1 = p_ifm_ext_d0;
 //on stdcore[3]: port p_valve2 = XS1_PORT_1E;
 //on stdcore[3]: port p_valve3 = XS1_PORT_1J;
 //on stdcore[3]: port p_valve4 = XS1_PORT_1B;
 //::Ports End

 // IP Config - change this to suit your network.  Leave with all
 // 0 values to use DHCP
 #ifdef DHCP
 xtcp_ipconfig_t ipconfig = { { 0, 0, 0, 0 }, // ip address (eg 192,168,0,2)
 		{ 0, 0, 0, 0 }, // netmask (eg 255,255,255,0)
 		{ 0, 0, 0, 0 } // gateway (eg 192,168,0,1)
 };
 #else
 xtcp_ipconfig_t ipconfig = {
 	{	169, 254, 196, 178},
 	{	255, 255, 0, 0},
 	{	0, 0, 0, 0}
 };
 #endif

  // Wireless access point config: SSID, Key, Security Type
 wifi_ap_config_t ap_config = { WIFI_SSID, WIFI_PASSWORD, WIFI_SECURITY_TYPE };

 void tcp_handler(chanend c_xtcp, chanend c_gpio) {
 	xtcp_connection_t conn;

 	// Switch ON the Wi-Fi module
 	xtcp_wifi_on(c_xtcp);
 	// Connect to an access point
 	xtcp_connect(c_xtcp, ap_config);

 	web_server_init(c_xtcp, null, null);
 	init_web_state(c_gpio);
 	while (1) {
 		select
 		{
 			case xtcp_event(c_xtcp,conn):
 			web_server_handle_event(c_xtcp, null, null, conn);
 			break;
 		}
 	}
 }


/*
 * Motor Control Stuff
 */

//#define ENABLE_xscope_main
#define COM_CORE 0
#define IFM_CORE 3

on stdcore[IFM_CORE]: clock clk_adc = XS1_CLKBLK_1;
on stdcore[IFM_CORE]: clock clk_pwm = XS1_CLKBLK_REF;

#define HALL 1
#define QEI 2


void xscope_initialise_1()
{
	xscope_register(2, XSCOPE_CONTINUOUS, "0 actual_position", XSCOPE_INT,	"n",
						XSCOPE_CONTINUOUS, "1 target_position", XSCOPE_INT, "n");

	xscope_config_io(XSCOPE_IO_BASIC);
	return;
}



void position_profile_test(chanend c_position_ctrl)
{
	int target_position = 50;			// degree
	int velocity 		= 100;			// rpm
	int acceleration 	= 100;			// rpm/s
	int deceleration 	= 100;     		// rpm/s
	printstrln("into position profile test!");

	init_position_profile_limits(GEAR_RATIO, MAX_ACCELERATION, MAX_PROFILE_VELOCITY);

#ifdef ENABLE_xscope_main
	xscope_initialise_1();
#endif

	set_profile_position(target_position, velocity, acceleration, deceleration, c_position_ctrl);

	//target_position = 0; 	//degree
	//set_profile_position(target_position, velocity, acceleration, deceleration, c_position_ctrl);
}


/*
 * entry point to the program
 */
int main(void)
{
	//wifi stuff
	chan c_xtcp[1];
	chan c_gpio;

	//motor control stuff
	chan c_adctrig;
	chan c_qei_p1, c_qei_p2, c_qei_p3, c_qei_p4, c_qei_p5 ;
	chan c_hall_p1, c_hall_p2, c_hall_p3, c_hall_p4, c_hall_p5;
	chan c_commutation_p1, c_commutation_p2, c_commutation_p3;
	chan c_pwm_ctrl;
	chan c_signal_adc;
	chan c_sig_1, c_signal, c_sync;
	chan c_position_ctrl;

	par
	{

		on stdcore[COM_CORE]:
		{
			printstrln("into wifi loop...");
			ext_ant<:0; //wsitch between external and internal antenna
			wifi_tiwisl_server(c_xtcp[0], tiwisl_spi, tiwisl_ctrl);
		}

		on stdcore[0]:
		tcp_handler(c_xtcp[0], c_gpio);

		on stdcore[IFM_CORE]:
		{
			app_handler(c_position_ctrl, c_gpio, p_valve1, p_valve2, p_valve3, p_valve4);

		}


		on stdcore[2]:
		{
			{
				 ctrl_par position_ctrl_params;
				 hall_par hall_params;
				 qei_par qei_params;

				 init_position_control_param(position_ctrl_params);
				 init_hall_param(hall_params);
				 init_qei_param(qei_params);

				 position_control(position_ctrl_params, hall_params, qei_params, HALL, c_hall_p2,\
						 c_qei_p1, c_position_ctrl, c_commutation_p3);
			}

		}

		/************************************************************
		 * IFM_CORE
		 ************************************************************/
		on stdcore[IFM_CORE]:
		{
			par
			{

				do_pwm_inv_triggered(c_pwm_ctrl, c_adctrig, p_ifm_dummy_port,
						p_ifm_motor_hi, p_ifm_motor_lo, clk_pwm);

				{
					hall_par hall_params;
					qei_par qei_params;
					commutation_par commutation_params;
					init_hall_param(hall_params);
					init_qei_param(qei_params);
					init_commutation_param(commutation_params, hall_params, MAX_NOMINAL_SPEED); 			// initialize commutation params
					commutation_sinusoidal(c_hall_p1,  c_qei_p2, c_signal, c_sync, \
							c_commutation_p1, c_commutation_p2, c_commutation_p3, \
							c_pwm_ctrl, hall_params, qei_params, commutation_params);
				}

				{
					hall_par hall_params;
					init_hall_param(hall_params);
					run_hall(c_hall_p1, c_hall_p2, c_hall_p3, c_hall_p4, c_hall_p5, p_ifm_hall, hall_params); // channel priority 1,2..4
				}

				{
					qei_par qei_params;
					init_qei_param(qei_params);
					run_qei(c_qei_p1, c_qei_p2, c_qei_p3, c_qei_p4, c_qei_p5, p_ifm_encoder, qei_params);  // channel priority 1,2..4
				}

			}
		}

	}

	return 0;
}
