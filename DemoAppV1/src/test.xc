#include <platform.h>
#include <xs1.h>
#include <print.h>
#include <stdio.h>

on stdcore[3]: out port vent0 = XS1_PORT_1B;
//on stdcore[3]: out port vent0 =XS1_PORT_4A;
#define FLASH_PERIOD 200000000
//#define ON_PERIOD 	  1000000000

/*
 * function that toggles between on and off at the specified FLASH_PERIOD
 */
void my_application()
{
	  timer tmr;
	  unsigned isOn = 1;
	  unsigned t;
	  tmr :> t;
	  while (1) {
		vent0 <: isOn;
		t += FLASH_PERIOD;
		tmr when timerafter (t) :> void;
		isOn = !isOn;
	  }
}

/*
 * function that toggles between on and off based on user input
 */
void printing()
{
	while (1)
	{
		  char c;
		  unsigned isOn = 1;
		  printstr("Enter 'y' to switch on and n to switch off, then press enter:");
		  c = getchar();
		  printstr("The character input is: ");
		  if (c == 'y')
		  {
			  vent0 <: isOn;
		  }
		  else if(c == 'n')
		  {
			  vent0 <: !isOn;
		  }
		  //return 0;
	}

}

/*
 * prototype function to develop timing for different recipes
 *
 */
void makeRecipe()
{
		  timer tmr;
		  unsigned isOn = 1;
		  unsigned t;
		  int ON_PERIOD = 1000000000;
		  tmr :> t;

			vent0 <: isOn;
			t += ON_PERIOD;
			tmr when timerafter (t) :> void;
			isOn = !isOn;
}


/*
 * main function for the application
 */
int main(void)
{
	par
	{
		on stdcore[3]: printing();

	}
}
