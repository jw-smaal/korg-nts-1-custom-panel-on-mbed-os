/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "AnalogIn.h"
#include "DigitalOut.h"
#include "PinNames.h"
#include "mbed.h"
#include "mbed_wait_api.h"
#include "nts-1.h"
#include "stm32f030x8.h"
#include <cstdint>

#define WAIT_TIME_MS 500 



DigitalOut led4(PF_7);
//DigitalOut led2(PB_7);
//DigitalOut d8(PA_9);
AnalogIn ain(PC_2);

int main()
{
	NTS1 nts1; 
	uint8_t i, j; 

    printf("Korg NTS-1 Custom Board used with MBED OS code by: J-W Smaal, running on Mbed OS %d.%d.%d.\n\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);
	printf("nts1.init() status %2X\n", nts1.init());
	wait_ms(200);

    while (true)
    {
		printf("Potmeter value is: %u\r\n", ain.read_u16());
        led4 = !led4;
//		led2 = !led2; 
//		d8 = !d8;


		for(i=60; i < 70; i++) {
			nts1.noteOn(i, 100);
			wait_ms(40);
			nts1.idle();

			nts1.noteOff(i);
			wait_ms(40);
			nts1.idle();  
		}
		wait_ms(200);
		nts1.idle(); 
		//printf("nts1.idle() called (board should not reset!)\r\n");
        
        //thread_sleep_for(WAIT_TIME_MS);
		//ThisThread::sleep_for(500ms);
    }
	nts1.teardown(); 
}
