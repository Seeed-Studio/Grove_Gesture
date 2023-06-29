/*
    pag7660.h
    A library for Grove-Gesture v1.0 & v2.0

    Copyright (c) 2023 seeed technology inc.
    Website    : www.seeed.cc
    Author     : JX.Weng
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


#ifndef __GESTURE_PAG7660_H__
#define __GESTURE_PAG7660_H__

#include <stdint.h>

#define PAG7660_I2C_ADDR    0x68
#define PAG7660_I2C_ADDR2   0x60
#define PAG7660_WIDTH       400
#define PAG7660_HEIGHT      400

enum pag7660_gesture_mode {
    GESTURE_THUMB_MODE      = 2,
    GESTURE_CURSOR_MODE     = 4,
    GESTURE_COMBINED_MODE   = 5, /* Default */
    NF_GESTURE_MODES,
};

#define GESTURE_MAX_TIPS    5
#define IS_VALID_TIP(tips, bit) (((tips) >> (bit)) & 1)
#define BIT8(x)             (((x) & 1) << 8)
#define BIT8_10(x)          (((x) & 7) << 8)

#pragma pack(1)

/* Gesture registers */
typedef struct pag7660_reg_valid {
    uint8_t palm : 1;
    uint8_t tips : GESTURE_MAX_TIPS;
    uint8_t __rsv : 2;
} pag7660_reg_valid_t;

typedef struct pag7660_reg_palm {
    uint8_t x;
    uint8_t y;
    uint8_t r;
    uint8_t b;
} pag7660_reg_palm_t;

typedef struct pag7660_reg_bit8 {
    uint8_t palm : 1;
    uint8_t tips : GESTURE_MAX_TIPS;
    uint8_t __rsv : 2;
} pag7660_reg_bit8_t;

typedef struct pag7660_reg_tip {
    uint8_t x;
    uint8_t y;
    uint8_t b;
    uint8_t id : 3;
    uint8_t __rsv : 5;
} pag7660_reg_tip_t;

typedef struct pag7660_reg_result {
    struct {
        uint8_t thumb_up : 1;
        uint8_t cursor_type : 2;
        uint8_t gesture_type : 5;
        uint8_t select : 1;
        uint8_t __rsv : 2;
        uint8_t zoom : 5;
        uint8_t cursor_x;
        uint8_t cursor_y;
        uint8_t thumb_down : 1;
        uint8_t __rsv2 : 7;
    } ges;
    int16_t ang_acc;
    struct {
        uint8_t binning : 1;
        uint8_t __rsv : 7;
        uint8_t x;
        uint8_t y;
    } crop;
    struct {
        uint8_t x : 3;
        uint8_t y : 3;
        uint8_t __rsv : 2;
    } cursor_hb;
} pag7660_reg_result_t;

typedef struct pag7660_reg_out {
    pag7660_reg_valid_t valid;
    pag7660_reg_palm_t palm;
    pag7660_reg_bit8_t bit8[2];
    pag7660_reg_tip_t tips[GESTURE_MAX_TIPS];
    pag7660_reg_result_t result;
} pag7660_reg_out_t;

/* Gesture output */
typedef struct pag7660_palm {
    bool valid;
    uint16_t x;
    uint16_t y;
    uint8_t r;
    uint8_t b;
} pag7660_palm_t;

typedef struct pag7660_tip {
    uint8_t id;
    uint16_t x;
    uint16_t y;
    uint8_t b;
} pag7660_tip_t;

typedef struct pag7660_thumb {
    bool up;
    bool down;
} pag7660_thumb_t;

typedef struct pag7660_cursor {
    uint8_t type;
    bool select;
    uint16_t x;
    uint16_t y;
} pag7660_cursor_t;

typedef struct pag7660_crop {
    bool binning;
    uint8_t x;
    uint8_t y;
} pag7660_crop_t;

typedef struct pag7660_result {
    uint8_t type;
    int16_t rotate;
    uint8_t zoom;
    pag7660_thumb_t thumb;
    pag7660_cursor_t cursor;
    pag7660_crop_t crop;
} pag7660_result_t;

typedef struct pag7660_out {
    pag7660_palm_t palm;
    uint8_t num_of_tips;
    pag7660_tip_t tips[GESTURE_MAX_TIPS];
    pag7660_result_t result;
} pag7660_out_t;

#pragma pack()

typedef pag7660_result_t pag7660_gesture_t;

#endif /* __GESTURE_PAG7660_H__ */