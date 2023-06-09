/*
    paj7620.cpp
    A library for Grove-Gesture 1.0

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

#include "paj7620.h"

#if defined(__AVR__) || defined(ARDUINO_ARCH_ESP8266) || defined(ARDUINO_ARCH_ESP32)
#define PROGMEM_COMPATIBLE
const uint8_t initRegisterArray[][2] PROGMEM = {
#else
const uint8_t initRegisterArray[][2] = {
#endif
    {0xEF,0x00}, {0x37,0x07}, {0x38,0x17}, {0x39,0x06},
    {0x42,0x01}, {0x46,0x2D}, {0x47,0x0F}, {0x48,0x3C},
    {0x49,0x00}, {0x4A,0x1E}, {0x4C,0x20}, {0x51,0x10},
    {0x5E,0x10}, {0x60,0x27}, {0x80,0x42}, {0x81,0x44},
    {0x82,0x04}, {0x8B,0x01}, {0x90,0x06}, //{0x91,0x0A}
    {0x95,0x0A}, {0x96,0x0C}, {0x97,0x05}, {0x9A,0x14},
    {0x9C,0x3F}, {0xA5,0x19}, {0xCC,0x19}, {0xCD,0x0B},
    {0xCE,0x13}, {0xCF,0x64}, {0xD0,0x21}, {0xEF,0x01},
    {0x02,0x0F}, {0x03,0x10}, {0x04,0x02}, {0x25,0x01},
    {0x27,0x39}, {0x28,0x7F}, {0x29,0x08}, {0x3E,0xFF},
    {0x5E,0x3D}, {0x65,0x96}, {0x67,0x97}, {0x69,0xCD},
    {0x6A,0x01}, {0x6D,0x2C}, {0x6E,0x01}, {0x72,0x01},
    {0x73,0x35}, {0x77,0x01}, {0xEF,0x00},
};

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
    paj7620WriteReg(PAJ7620_REGITER_BANK_SEL, 0);
    paj7620WriteReg(PAJ7620_REGITER_BANK_SEL, 0);

    paj7620ReadReg(0, 1, &data0);
    paj7620ReadReg(1, 1, &data1);
    if ((data0 != 0x20) || (data1 != 0x76)) {
        return 0xff;
    }
    Serial.println("wake-up finish.");

	for(uint8_t i = 0; i < INIT_REG_ARRAY_SIZE; i++) {
		#ifdef PROGMEM_COMPATIBLE
		data0 = pgm_read_word(&initRegisterArray[i][0]);
		data1 = pgm_read_word(&initRegisterArray[i][1]);
		#else
		data0 = initRegisterArray[i][0];
		data1 = initRegisterArray[i][1];
		#endif
		paj7620WriteReg(data0, data1);
	}

	setReportMode(NEAR_240FPS);
    paj7620WriteReg(PAJ7620_REGITER_BANK_SEL, 0);  //gesture flage reg in Bank0

    Serial.println("Paj7620 initialize register finished.");
    return 0;
}

/**
    Setting normal mode or gaming mode at BANK1 register 0x65/0x66 R_IDLE_TIME[15:0]
	T = 256/System CLK = 32us,
*/
void setReportMode(uint8_t reportMode) {
	uint8_t regIdleTime = 0;
	paj7620WriteReg(PAJ7620_REGITER_BANK_SEL, 1);  //gesture flage reg in Bank1
	switch (reportMode) {
	// Far Mode: 1 report time = (77 + R_IDLE_TIME) * T
    case FAR_240FPS:
		regIdleTime = 53; // 1/(240*T) - 77
        break;
    case FAR_120FPS:
        regIdleTime = 183; // 1/(120*T) - 77
        break;
	// Near Mode: 1 report time = (112 + R_IDLE_TIME) * T
    case NEAR_240FPS:
        regIdleTime = 18; // 1/(240*T) - 112
        break;
	case NEAR_120FPS:
        regIdleTime = 148; // 1/(120*T) - 112
        break;
    default:
        break;
    }
	paj7620WriteReg(0x65, regIdleTime);
	paj7620WriteReg(PAJ7620_REGITER_BANK_SEL, 0);  //gesture flage reg in Bank0
}
