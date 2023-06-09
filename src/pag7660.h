#ifndef __GESTURE_PAG7660_H__
#define __GESTURE_PAG7660_H__

#include <stdint.h>

#define PAG7660_I2C_ADDR 0x40
#define PAG7660_ID          0x7660
#define PAG7660_I2C_ADDRESS (0x40 << 1)
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
typedef struct gesture_reg_valid {
    uint8_t palm : 1;
    uint8_t tips : GESTURE_MAX_TIPS;
    uint8_t __rsv : 2;
} gesture_reg_valid_t;

typedef struct gesture_reg_palm {
    uint8_t x;
    uint8_t y;
    uint8_t r;
    uint8_t b;
} gesture_reg_palm_t;

typedef struct gesture_reg_bit8 {
    uint8_t palm : 1;
    uint8_t tips : GESTURE_MAX_TIPS;
    uint8_t __rsv : 2;
} gesture_reg_bit8_t;

typedef struct gesture_reg_tip {
    uint8_t x;
    uint8_t y;
    uint8_t b;
    uint8_t id : 3;
    uint8_t __rsv : 5;
} gesture_reg_tip_t;

typedef struct gesture_reg_result {
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
} gesture_reg_result_t;

typedef struct gesture_reg_out {
    gesture_reg_valid_t valid;
    gesture_reg_palm_t palm;
    gesture_reg_bit8_t bit8[2];
    gesture_reg_tip_t tips[GESTURE_MAX_TIPS];
    gesture_reg_result_t result;
} gesture_reg_out_t;

/* Gesture output */
typedef struct gesture_palm {
    bool valid;
    uint16_t x;
    uint16_t y;
    uint8_t r;
    uint8_t b;
} gesture_palm_t;

typedef struct gesture_tip {
    uint8_t id;
    uint16_t x;
    uint16_t y;
    uint8_t b;
} gesture_tip_t;

typedef struct gesture_thumb {
    bool up;
    bool down;
} gesture_thumb_t;

typedef struct gesture_cursor {
    uint8_t type;
    bool select;
    uint16_t x;
    uint16_t y;
} gesture_cursor_t;

typedef struct gesture_crop {
    bool binning;
    uint8_t x;
    uint8_t y;
} gesture_crop_t;

typedef struct gesture_result {
    uint8_t type;
    int16_t rotate;
    uint8_t zoom;
    gesture_thumb_t thumb;
    gesture_cursor_t cursor;
    gesture_crop_t crop;
} gesture_result_t;

typedef struct gesture_out {
    gesture_palm_t palm;
    uint8_t num_of_tips;
    gesture_tip_t tips[GESTURE_MAX_TIPS];
    gesture_result_t result;
} gesture_out_t;

#pragma pack()

static gesture_out_t toGesture(const gesture_reg_out_t& reg) {
    gesture_out_t out;
    /* Reset gesture output */
    memset(&out, 0, sizeof(out));
    
    /* Read palm */
    if (reg.valid.palm) {
        out.palm.valid = true;
        out.palm.x = reg.palm.x | BIT8(reg.bit8[0].palm);
        out.palm.y = reg.palm.y | BIT8(reg.bit8[1].palm);
        out.palm.r = reg.palm.r;
        out.palm.b = reg.palm.b;
    }
    
    /* Read tips */
    if (reg.valid.tips) {
        for (int i = 0; i < GESTURE_MAX_TIPS; i++) {
            if (IS_VALID_TIP(reg.valid.tips, i)) {
                out.tips[out.num_of_tips].x = reg.tips[i].x | BIT8(IS_VALID_TIP(reg.bit8[0].tips, i));
                out.tips[out.num_of_tips].y = reg.tips[i].y | BIT8(IS_VALID_TIP(reg.bit8[1].tips, i));
                out.tips[out.num_of_tips].b = reg.tips[i].b;
                out.tips[out.num_of_tips].id = reg.tips[i].id;
                out.num_of_tips++;
            }
        }
    }
    
    /* Read result */
    out.result.type = reg.result.ges.gesture_type;
    out.result.rotate = reg.result.ang_acc;
    out.result.zoom = reg.result.ges.zoom;
    out.result.thumb.up = reg.result.ges.thumb_up;
    out.result.thumb.down = reg.result.ges.thumb_down;
    out.result.cursor.type = reg.result.ges.cursor_type;
    out.result.cursor.select = reg.result.ges.select;
    out.result.cursor.x = reg.result.ges.cursor_x | BIT8_10(reg.result.cursor_hb.x);
    out.result.cursor.y = reg.result.ges.cursor_y | BIT8_10(reg.result.cursor_hb.y);
    out.result.crop.binning = reg.result.crop.binning;
    out.result.crop.x = reg.result.crop.x;
    out.result.crop.y = reg.result.crop.y;
    
    return out;
}

#endif /* __GESTURE_PAG7660_H__ */