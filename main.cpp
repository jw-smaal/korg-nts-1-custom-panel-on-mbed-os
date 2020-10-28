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
	wait_ms(30);
	nts1.idle();
	wait_ms(50);

    while (true)
    {
        led4 = !led4;
		printf("Potmeter value is: %u\r\n", ain.read_u16()>>8);
		nts1.paramChange(	NTS1::PARAM_ID_REV_DEPTH, 
							NTS1::PARAM_SUBID_SYS_GLOBAL_BASE , 
							(ain.read_u16()>>9));
		nts1.idle();


		nts1.paramChange(	NTS1::PARAM_ID_OSC_SHAPE, 
							NTS1::PARAM_SUBID_SYS_GLOBAL_BASE , 
							(ain.read_u16()>>9));

		nts1.noteOn(70, 100);
		wait_ms(70);
		nts1.idle();

		nts1.noteOn(72, 100);
		wait_ms(60);
		nts1.idle();

		nts1.noteOff(70);
		wait_ms(10);
		nts1.idle();
		
		nts1.noteOff(72);
		wait_ms(10);
		nts1.idle();

		nts1.noteOn(74, 100);
		wait_ms(150);
		nts1.idle();
}

	nts1.teardown(); 
}
