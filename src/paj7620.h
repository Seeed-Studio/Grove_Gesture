/*
    paj7620.h
    A library for Grove-Gesture 1.0

    Copyright (c) 2023 seeed technology inc.
    Website    : www.seeed.cc
    Author     : Wuruibin & Xiangnan
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


#ifndef __GESTURE_PAJ7620_H__
#define __GESTURE_PAJ7620_H__

#define PAJ7620_I2C_ADDR	0x73
// REGISTER DESCRIPTION
#define PAJ7620_REG_BANK_SEL  0xEF
#define PAJ7620_REG_RESULT_L  0x43
#define PAJ7620_REG_RESULT_H  0x44

#define PAJ7620_GESTURE_COUNT 9
typedef enum paj7620_gesture_type {
    UP,DOWN,LEFT,RIGHT,PUSH,POLL,CLOCKWISE,ANTI_CLOCKWISE,WAVE
} paj7620_gesture_type_t;
typedef paj7620_gesture_type_t paj7620_gesture_t;

typedef enum paj7620_report_mode {
    FAR_240FPS, FAR_120FPS, NEAR_240FPS, NEAR_120FPS
} paj7620_report_t;

const uint8_t initRegisterArray[][2] = {
    // BANK 0
    {0xEF,0x00}, {0x37,0x07}, {0x38,0x17}, {0x39,0x06}, {0x42,0x01}, 
    {0x46,0x2D}, {0x47,0x0F}, {0x48,0x3C}, {0x49,0x00}, {0x4A,0x1E}, 
    {0x4C,0x20}, {0x51,0x10}, {0x5E,0x10}, {0x60,0x27}, {0x80,0x42}, 
    {0x81,0x44}, {0x82,0x04}, {0x8B,0x01}, {0x90,0x06}, {0x95,0x0A}, 
    {0x96,0x0C}, {0x97,0x05}, {0x9A,0x14}, {0x9C,0x3F}, {0xA5,0x19}, 
    {0xCC,0x19}, {0xCD,0x0B}, {0xCE,0x13}, {0xCF,0x64}, {0xD0,0x21}, 
    // BANK 1
    {0xEF,0x01}, {0x02,0x0F}, {0x03,0x10}, {0x04,0x02}, {0x25,0x01},
    {0x27,0x39}, {0x28,0x7F}, {0x29,0x08}, {0x3E,0xFF}, {0x5E,0x3D}, 
    {0x65,0x96}, {0x67,0x97}, {0x69,0xCD}, {0x6A,0x01}, {0x6D,0x2C}, 
    {0x6E,0x01}, {0x72,0x01}, {0x73,0x35}, {0x77,0x01}, {0xEF,0x00},
};
#define INIT_REG_ARRAY_SIZE (sizeof(initRegisterArray)/sizeof(initRegisterArray[0]))

#endif
