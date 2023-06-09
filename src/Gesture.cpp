/*
    Gesture.cpp
    A library for Grove - Gesture Sensor

    Copyright (c) 2023 seeed technology inc.
    Website    : www.seeed.cc
    Author     : Jx.Weng
    Modified Time: June 2023

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

#include "Gesture.h"

void Pixart_Gesture::writeReg(uint8_t addr, uint8_t value) {
    Wire.beginTransmission(i2c_addr);
    Wire.write(addr);
    Wire.write(value);
    if (0 != Wire.endTransmission()) {
        Serial.print("Transmission error!!!\n");
    }
}

void Pixart_Gesture::readRegs(uint8_t addr, uint8_t *values, int size) {
    Wire.beginTransmission(i2c_addr);
    Wire.write(addr);
    if (0 != Wire.endTransmission()) {
        Serial.print("Transmission error!!!\n");
    }

    Wire.requestFrom((int)i2c_addr, (int)size);
    while (Wire.available()) {
        *values = Wire.read();
        values++;
    }
}

uint8_t Pixart_Gesture::readReg(uint8_t addr) {
    uint8_t values;
    readRegs(addr, &values, 1);
    return values;
}

bool paj7620::init()
{   
    delay(10);
    Wire.begin();
    writeReg(0xff, 0x00);  //wakeup
    delay(50);

    if((readReg(0x00) != 0x20) || (readReg(0x01) != 0x76))
        return false;
    delay(10);
    for(uint8_t i = 0; i < INIT_REG_ARRAY_SIZE; i++)
        writeReg(initRegisterArray[i][0], initRegisterArray[i][1]);
    
    setReportMode(NEAR_240FPS);
    return true;
}

bool paj7620::getResult(paj7620_gesture_t& out)
{
    uint16_t gesture_code;
    gesture_code = (readReg(PAJ7620_REG_RESULT_H)<<8) + readReg(PAJ7620_REG_RESULT_L);
    if (gesture_code == 0) return false;
    for (uint8_t i = UP; i < PAJ7620_GESTURE_COUNT; i++)
    {
        if (gesture_code == (1 << i)) {
            out = (paj7620_gesture_t)i;
            readReg(PAJ7620_REG_RESULT_H);
            readReg(PAJ7620_REG_RESULT_L);
            return true;
        }
    }
    return false;
}

/**
    Setting normal mode or gaming mode at BANK1 register 0x65/0x66 R_IDLE_TIME[15:0]
	T = 256/System CLK = 32us,
*/
bool paj7620::setReportMode(uint8_t reportMode) {
    uint8_t regIdleTime = 0;
	writeReg(PAJ7620_REG_BANK_SEL, 1);  // reg in Bank1
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
        return false;
    }
	writeReg(0x65, regIdleTime);
	writeReg(PAJ7620_REG_BANK_SEL, 0);  // reg in Bank0
    return true;
}


bool pag7660::init() {
    const uint8_t regs[][2] = {
        { 0x10, 0x04 },        // Set operation to gesture mode
        { 0x22, gestureMode }, // Set gesture mode
        { 0x0A, 0x01 },        // enable cpu
    };
    uint16_t id;
    id = (readReg(1) << 8) | readReg(0);
    if (id != PAG7660_ID)
        return false;
    
    for (int i = 0; i < sizeof(regs)/2; i++) {
        writeReg(regs[i][0], regs[i][1]);
        delay(10);
    }
    return true;
}

int pag7660::getGestureMode() {
    return gestureMode;
}

int pag7660::nextGestureMode() {
    /* Determine next gesture mode */
    switch (gestureMode) {
    case GESTURE_THUMB_MODE:
        gestureMode = GESTURE_CURSOR_MODE;
        break;
    case GESTURE_CURSOR_MODE:
        gestureMode = GESTURE_COMBINED_MODE;
        break;
    case GESTURE_COMBINED_MODE:
        gestureMode = GESTURE_THUMB_MODE;
        break;
    default:
        gestureMode = GESTURE_COMBINED_MODE;
        break;
    }
    /* Switch gesture mode */
    writeReg(0x22, gestureMode);
    return gestureMode;
}

bool pag7660::getGestureOutput(gesture_out_t& out) {
    /* Check frame ready */
    if (!checkReady())
        return false;
    /* Read gesture output */
    gesture_reg_out_t reg;
    readRegs(0x3c, (uint8_t *)&reg, sizeof(reg));
    out = toGesture(reg);
    /* Clear frame ready */
    clearReady();
    return true;
}

bool pag7660::checkReady() {
    return readReg(0x04) & 0x02;
}

void pag7660::clearReady() {
    writeReg(0x04, 0x00);
}