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

// REGISTER DESCRIPTION
#define PAJ7620_VAL(maskbit)		( 1 << maskbit )
#define PAJ7620_ADDR_BASE				0x00

// REGISTER BANK SELECT
#define PAJ7620_REGITER_BANK_SEL		(PAJ7620_ADDR_BASE + 0xEF)	//W

// DEVICE ID
#define PAJ7620_ID  0x73

// REGISTER BANK 0
#define PAJ7620_ADDR_SUSPEND_CMD		(PAJ7620_ADDR_BASE + 0x3)	//W
#define PAJ7620_ADDR_GES_PS_DET_MASK_0	(PAJ7620_ADDR_BASE + 0x41)	//RW
#define PAJ7620_ADDR_GES_PS_DET_MASK_1	(PAJ7620_ADDR_BASE + 0x42)	//RW
#define PAJ7620_ADDR_GES_PS_DET_FLAG_0	(PAJ7620_ADDR_BASE + 0x43)	//R
#define PAJ7620_ADDR_GES_PS_DET_FLAG_1	(PAJ7620_ADDR_BASE + 0x44)	//R
#define PAJ7620_ADDR_STATE_INDICATOR	(PAJ7620_ADDR_BASE + 0x45)	//R
#define PAJ7620_ADDR_PS_HIGH_THRESHOLD	(PAJ7620_ADDR_BASE + 0x69)	//RW
#define PAJ7620_ADDR_PS_LOW_THRESHOLD	(PAJ7620_ADDR_BASE + 0x6A)	//RW
#define PAJ7620_ADDR_PS_APPROACH_STATE	(PAJ7620_ADDR_BASE + 0x6B)	//R
#define PAJ7620_ADDR_PS_RAW_DATA		(PAJ7620_ADDR_BASE + 0x6C)	//R

// REGISTER BANK 1
#define PAJ7620_ADDR_PS_GAIN			(PAJ7620_ADDR_BASE + 0x44)	//RW
#define PAJ7620_ADDR_IDLE_S1_STEP_0		(PAJ7620_ADDR_BASE + 0x67)	//RW
#define PAJ7620_ADDR_IDLE_S1_STEP_1		(PAJ7620_ADDR_BASE + 0x68)	//RW
#define PAJ7620_ADDR_IDLE_S2_STEP_0		(PAJ7620_ADDR_BASE + 0x69)	//RW
#define PAJ7620_ADDR_IDLE_S2_STEP_1		(PAJ7620_ADDR_BASE + 0x6A)	//RW
#define PAJ7620_ADDR_OP_TO_S1_STEP_0	(PAJ7620_ADDR_BASE + 0x6B)	//RW
#define PAJ7620_ADDR_OP_TO_S1_STEP_1	(PAJ7620_ADDR_BASE + 0x6C)	//RW
#define PAJ7620_ADDR_OP_TO_S2_STEP_0	(PAJ7620_ADDR_BASE + 0x6D)	//RW
#define PAJ7620_ADDR_OP_TO_S2_STEP_1	(PAJ7620_ADDR_BASE + 0x6E)	//RW
#define PAJ7620_ADDR_OPERATION_ENABLE	(PAJ7620_ADDR_BASE + 0x72)	//RW

#define PAJ7620_GESTURE_COUNT 9
typedef enum PAJ7620_GESTURE {
    RIGHT,LEFT,UP,DOWN,PUSH,POLL,CLOCKWISE,ANTI_CLOCKWISE,WAVE
} paj7620_gesture_t;

#define INIT_REG_ARRAY_SIZE (sizeof(initRegisterArray)/sizeof(initRegisterArray[0]))


uint8_t paj7620Init(void);
uint8_t paj7620WriteReg(uint8_t addr, uint8_t cmd);
uint8_t paj7620ReadReg(uint8_t addr, uint8_t qty, uint8_t data[]);


#endif
