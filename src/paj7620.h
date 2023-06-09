/*
    paj7620.h
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


#ifndef __PAJ7620_H__
#define __PAJ7620_H__

#include <Arduino.h>
#include <Wire.h>

// REGISTER DESCRIPTION
#define PAJ7620_VAL(maskbit)		( 1 << maskbit )
#define PAJ7620_ADDR_BASE				0x00

// REGISTER BANK SELECT
#define PAJ7620_REGITER_BANK_SEL	0xEF	//W

// DEVICE ID
#define PAJ7620_ID  0x73

#define PAJ7620_GESTURE_COUNT 9
typedef enum PAJ7620_GESTURE {
    RIGHT,LEFT,UP,DOWN,PUSH,POLL,CLOCKWISE,ANTI_CLOCKWISE,WAVE
} paj7620_gesture_t;

enum paj7620_report_mode {
    FAR_240FPS = 0,
    FAR_120FPS,
    NEAR_240FPS, /* Default */
    NEAR_120FPS
};

#define INIT_REG_ARRAY_SIZE (sizeof(initRegisterArray)/sizeof(initRegisterArray[0]))


uint8_t paj7620Init(void);
uint8_t paj7620WriteReg(uint8_t addr, uint8_t cmd);
uint8_t paj7620ReadReg(uint8_t addr, uint8_t qty, uint8_t data[]);
void setReportMode(uint8_t reportMode);


#endif
