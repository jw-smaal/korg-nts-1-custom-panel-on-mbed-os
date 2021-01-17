/** Example for the Korg NTS-1 Custom panel on MBED OS 
 *  @author Jan-Willem Smaal <usenet@gispen.org> 
 * 
 * 
 * @license: BSD 3-Clause License
 */

#include "AnalogIn.h"
#include "BusOut.h"
#include "DigitalIn.h"
#include "DigitalOut.h"
#include "PeripheralNames.h"
#include "PinNames.h"
#include "PinNamesTypes.h"
#include "PwmOut.h"
#include "mbed.h"
#include "mbed_thread.h"
#include "mbed_wait_api.h"
#include "nts-1.h"
#include "stm32f030x8.h"
#include <cstdint>

#define WAIT_TIME_MS 500 
#define PWM  0 



int main()
{
	NTS1 nts1; 
	// Outputs 
	DigitalOut led1(PC_10);
	DigitalOut led2(PC_12);
	DigitalOut led3(PF_6);
	DigitalOut led4(PF_7);
	DigitalOut led5(PA_15);
	DigitalOut led6(PB_7);
	DigitalOut led7(PC_13);
	DigitalOut led8(PC_14);

	BusOut panelled(
		PC_10, PC_12, PF_6, PF_7,
		PA_15, PB_7, PC_13, PC_14); 

	// Push switches also enable internal pull-up  
	DigitalIn sw1(PC_8);
	sw1.mode(PinMode::PullDown);
	DigitalIn sw2(PC_6);
	DigitalIn sw3(PC_5);
	DigitalIn sw4(PA_12);
	DigitalIn sw5(PA_11);
	DigitalIn sw6(PB_11);
	DigitalIn sw7(PB_2);
	DigitalIn sw8(PB_1);
	DigitalIn sw9(PC_4);
	DigitalIn sw10(PF_5);
	BusIn switches(
		PC_8, PC_6, PC_5, PA_12,
		PA_11, PB_11, PB_2, PB_1,
		PC_4, PF_5 
	);
	switches.mode(PinMode::PullDown);


#if PWM
	PwmOut pwmD9();
	pwmD9 = 0.1F; 
	pwmD9.period_ms(10);
#endif 


	AnalogIn ain(PC_2);
	AnalogIn ribbon(PA_0);
	
	uint8_t i, j;
	uint16_t val; 

    printf("Korg NTS-1 Custom Panel used with MBED OS code by: J-W Smaal, \
running on Mbed OS %d.%d.%d.\n", \ 
MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);
	printf("nts1.init() status %2X\n\n", nts1.init());


	// Setting up some initial parameters to play with  
	nts1.paramChange(NTS1::PARAM_ID_REV_BASE, 0, 1);
	nts1.paramChange(NTS1::PARAM_ID_REV_TIME, 0, 130); 
	nts1.paramChange(NTS1::PARAM_ID_REV_MIX, 0, 130); 
	nts1.paramChange(NTS1::PARAM_ID_ARP_STATE, 0, 2);
	nts1.paramChange(NTS1::PARAM_ID_FILT_TYPE, 0, 1);
	nts1.paramChange(NTS1::PARAM_ID_ARP_TEMPO, 0, 90);

    while (true)
    {
        //led4 = !led4;
		val = ribbon.read_u16()>>9; 
		#if PWM
		pwmD9 = (float)val/127.0F;
		#endif 

		printf("Ribbon value is: %u\r\n", val);
		nts1.paramChange(	NTS1::PARAM_ID_OSC_TYPE,
							0, 
							val ); 
		nts1.idle();
		nts1.paramChange(	NTS1::PARAM_ID_ARP_PATTERN, 
							0, 
							(ain.read_u16()>>9));
		nts1.idle();

		// Play one note. 
		nts1.noteOn(val, 100);
		wait_ms(70);
		nts1.idle();

		//nts1.noteOff(val);
	
		//	nts1.noteOff(val);
		//	wait_ms(10);
		//	nts1.idle();

		for(i = 0; i < 9; j = 1<<i, i++) {
			panelled = j; 
			wait_ms(100);
			nts1.idle();

			val = ribbon.read_u16()>>9;  
			nts1.paramChange(	NTS1::PARAM_ID_OSC_TYPE, 
								0, 
							val);
			if(sw1.read() == false) printf("Ribbon value is: %u\r\n", val);
			
			if(sw9.read() == false ) {
				nts1.paramChange(	NTS1::PARAM_ID_OSC_SHAPE,
								0, 
								val );
				wait_ms(100);
			} 
			if(sw10.read() == false)  {
				nts1.paramChange(	NTS1::PARAM_ID_FILT_CUTOFF,
								0, 
								val );
				wait_ms(100);
			} 


			val = ain.read_u16()>>13;
			if(sw1.read() == false ) printf("Knob value is: %u\r\n", val);
			nts1.paramChange(	NTS1::PARAM_ID_ARP_PATTERN, 
							0, 
							val);
			wait_ms(2);
			nts1.idle();
		}

	}  // End of while(true) 
	nts1.teardown(); 
	return -1;  

}	// End of main()

/* EOF */ 