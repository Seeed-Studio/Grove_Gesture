/*
    paj7620.cpp
    A library for Grove-Guesture 1.0

    Copyright (c) 2015 seeed technology inc.
    Website    : www.seeed.cc
    Author     : Wuruibin & Xiangnan
    Modified Time: June 2015

    The MIT License (MIT)

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE.
*/

#include <Wire.h>
#include "paj7620.h"
#include <Arduino.h>

// PAJ7620U2_20140305.asc
/* Registers' initialization data */
#if defined(__AVR__) || defined(ARDUINO_ARCH_ESP8266) || defined(ARDUINO_ARCH_ESP32)
#define PROGMEM_COMPATIBLE
const unsigned short initRegisterArray[] PROGMEM = {
#else
const unsigned short initRegisterArray[] = {
#endif
		// Initial Gesture // this is atleast 440 bytes
		0xEF00,
		0x3229,
		0x3301,
		0x3400,
		0x3501,
		0x3600,
		0x3707,
		0x3817,
		0x3906,
		0x3A12,
		0x3F00,
		0x4002,
		0x41FF,
		0x4201,
		0x462D,
		0x470F,
		0x483C,
		0x4900,
		0x4A1E,
		0x4B00,
		0x4C20,
		0x4D00,
		0x4E1A,
		0x4F14,
		0x5000,
		0x5110,
		0x5200,
		0x5C02,
		0x5D00,
		0x5E10,
		0x5F3F,
		0x6027,
		0x6128,
		0x6200,
		0x6303,
		0x64F7,
		0x6503,
		0x66D9,
		0x6703,
		0x6801,
		0x69C8,
		0x6A40,
		0x6D04,
		0x6E00,
		0x6F00,
		0x7080,
		0x7100,
		0x7200,
		0x7300,
		0x74F0,
		0x7500,
		0x8042,
		0x8144,
		0x8204,
		0x8320,
		0x8420,
		0x8500,
		0x8610,
		0x8700,
		0x8805,
		0x8918,
		0x8A10,
		0x8B01,
		0x8C37,
		0x8D00,
		0x8EF0,
		0x8F81,
		0x9006,
		0x9106,
		0x921E,
		0x930D,
		0x940A,
		0x950A,
		0x960C,
		0x9705,
		0x980A,
		0x9941,
		0x9A14,
		0x9B0A,
		0x9C3F,
		0x9D33,
		0x9EAE,
		0x9FF9,
		0xA048,
		0xA113,
		0xA210,
		0xA308,
		0xA430,
		0xA519,
		0xA610,
		0xA708,
		0xA824,
		0xA904,
		0xAA1E,
		0xAB1E,
		0xCC19,
		0xCD0B,
		0xCE13,
		0xCF64,
		0xD021,
		0xD10F,
		0xD288,
		0xE001,
		0xE104,
		0xE241,
		0xE3D6,
		0xE400,
		0xE50C,
		0xE60A,
		0xE700,
		0xE800,
		0xE900,
		0xEE07,
		0xEF01,
		0x001E,
		0x011E,
		0x020F,
		0x0310,
		0x0402,
		0x0500,
		0x06B0,
		0x0704,
		0x080D,
		0x090E,
		0x0A9C,
		0x0B04,
		0x0C05,
		0x0D0F,
		0x0E02,
		0x0F12,
		0x1002,
		0x1102,
		0x1200,
		0x1301,
		0x1405,
		0x1507,
		0x1605,
		0x1707,
		0x1801,
		0x1904,
		0x1A05,
		0x1B0C,
		0x1C2A,
		0x1D01,
		0x1E00,
		0x2100,
		0x2200,
		0x2300,
		0x2501,
		0x2600,
		0x2739,
		0x287F,
		0x2908,
		0x3003,
		0x3100,
		0x321A,
		0x331A,
		0x3407,
		0x3507,
		0x3601,
		0x37FF,
		0x3836,
		0x3907,
		0x3A00,
		0x3EFF,
		0x3F00,
		0x4077,
		0x4140,
		0x4200,
		0x4330,
		0x44A0,
		0x455C,
		0x4600,
		0x4700,
		0x4858,
		0x4A1E,
		0x4B1E,
		0x4C00,
		0x4D00,
		0x4EA0,
		0x4F80,
		0x5000,
		0x5100,
		0x5200,
		0x5300,
		0x5400,
		0x5780,
		0x5910,
		0x5A08,
		0x5B94,
		0x5CE8,
		0x5D08,
		0x5E3D,
		0x5F99,
		0x6045,
		0x6140,
		0x632D,
		0x6402,
		0x6596,
		0x6600,
		0x6797,
		0x6801,
		0x69CD,
		0x6A01,
		0x6BB0,
		0x6C04,
		0x6D2C,
		0x6E01,
		0x6F32,
		0x7100,
		0x7201,
		0x7335,
		0x7400,
		0x7533,
		0x7631,
		0x7701,
		0x7C84,
		0x7D03,
		0x7E01};

/****************************************************************
    Function Name: paj7620WriteReg
    Description:  PAJ7620 Write reg cmd
    Parameters: addr:reg address; cmd:function data
    Return: error code; success: return 0
****************************************************************/
uint8_t paj7620WriteReg(uint8_t addr, uint8_t cmd) {
    char i = 1;
    Wire.beginTransmission(PAJ7620_ID);		// start transmission to device
    //write cmd
    Wire.write(addr);						// send register address
    Wire.write(cmd);						// send value to write
    i = Wire.endTransmission();  		    // end transmission
    if (0 != i) {
        Serial.print("Transmission error!!!\n");
    }
    return i;
}

/****************************************************************
    Function Name: paj7620ReadReg
    Description:  PAJ7620 read reg data
    Parameters: addr:reg address;
 			   qty:number of data to read, addr continuously increase;
 			   data[]:storage memory start address
    Return: error code; success: return 0
****************************************************************/
uint8_t paj7620ReadReg(uint8_t addr, uint8_t qty, uint8_t data[]) {
    uint8_t error;
    Wire.beginTransmission(PAJ7620_ID);
    Wire.write(addr);
    error = Wire.endTransmission();

    if (0 != error) {
        Serial.print("Transmission error!!!\n");
        return error; //return error code
    }

    Wire.requestFrom((int)PAJ7620_ID, (int)qty);

    while (Wire.available()) {
        *data = Wire.read();

        #ifdef debug    //debug
        Serial.print("addr:");
        Serial.print(addr++, HEX);
        Serial.print("  data:");
        Serial.println(*data, HEX);
        #endif

        data++;
    }
    return 0;
}

/****************************************************************
    Function Name: paj7620SelectBank
    Description:  PAJ7620 select register bank
    Parameters: BANK0, BANK1
    Return: none
****************************************************************/
void paj7620SelectBank(bank_e bank) {
    switch (bank) {
        case BANK0:
            paj7620WriteReg(PAJ7620_REGITER_BANK_SEL, PAJ7620_BANK0);
            break;
        case BANK1:
            paj7620WriteReg(PAJ7620_REGITER_BANK_SEL, PAJ7620_BANK1);
            break;
        default:
            break;
    }
}

/****************************************************************
    Function Name: paj7620Init
    Description:  PAJ7620 REG INIT
    Parameters: none
    Return: error code; success: return 0
****************************************************************/
uint8_t paj7620Init(void) {
    //Near_normal_mode_V5_6.15mm_121017 for 940nm
    int i = 0;
    uint8_t error;
    uint8_t data0 = 0, data1 = 0;
    //wakeup the sensor
    delayMicroseconds(700);	//Wait 700us for PAJ7620U2 to stabilize

    Wire.begin();

    Serial.println("INIT SENSOR...");

    paj7620SelectBank(BANK0);
    paj7620SelectBank(BANK0);

    error = paj7620ReadReg(0, 1, &data0);
    if (error) {
        return error;
    }
    error = paj7620ReadReg(1, 1, &data1);
    if (error) {
        return error;
    }
    Serial.print("Addr0 =");
    Serial.print(data0, HEX);
    Serial.print(",  Addr1 =");
    Serial.println(data1, HEX);

    if ((data0 != 0x20) || (data1 != 0x76)) {
        return 0xff;
    }
    if (data0 == 0x20) {
        Serial.println("wake-up finish.");
    }

	for (i = 0; i < INIT_REG_ARRAY_SIZE; i++)
	{
        #ifdef PROGMEM_COMPATIBLE
		uint16_t word = pgm_read_word(&initRegisterArray[i]);
        #else
        uint16_t word = initRegisterArray[i];
        #endif
		uint8_t high, low;
		high = (word & 0xFF00) >> 8;
		low = (word & 0x00FF);
#ifdef debug
		Serial.print("Line :");
		Serial.print(i);
		Serial.print(" data: 0x");
		Serial.print(high, HEX);
		Serial.println(low, HEX);
#endif
		paj7620WriteReg(high, low);
    }

    /**
        Setting normal mode or gaming mode at BANK1 register 0x65/0x66 R_IDLE_TIME[15:0]
        T = 256/System CLK = 32us,
        Ex:
        Far Mode: 1 report time = (77+R_IDLE_TIME)T
        Report rate 120 fps:
        R_IDLE_TIME=1/(120*T)-77=183

        Report rate 240 fps:
        R_IDLE_TIME=1/(240*T)-77=53

        Near Mode: 1 report time = (112+R_IDLE_TIME)T

        Report rate 120 fps:
        R_IDLE_TIME=1/(120*T)-120=148

        Report rate 240 fps:
        R_IDLE_TIME=1/(240*T)-112=18

    */
    Serial.println("Set up gaming mode.");
    paj7620SelectBank(BANK1);  //gesture flage reg in Bank1
    // paj7620WriteReg(0x65, 0xB7); // far mode 120 fps
    paj7620WriteReg(0x65, 0x12);  // near mode 240 fps

    paj7620SelectBank(BANK0);  //gesture flage reg in Bank0

    Serial.println("Paj7620 initialize register finished.");
    return 0;
}
