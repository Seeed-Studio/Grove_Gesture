/*
    Gesture.cpp
    A library for Grove - Gesture Sensor

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

#include "Gesture.h"

void Pixart_Gesture::writeReg(uint8_t addr, uint8_t value) {
    if(spi_cs != GESTURE_SPI_USELESS) {
        digitalWrite(spi_cs, LOW);
        SPI.transfer(addr & 0x7f);
        SPI.transfer(value);
        digitalWrite(spi_cs, HIGH);
    } else {
        Wire.beginTransmission(i2c_addr);
        Wire.write(addr);
        Wire.write(value);
        Wire.endTransmission();
    }
}

void Pixart_Gesture::readRegs(uint8_t addr, uint8_t *values, int size) {
    if(spi_cs != GESTURE_SPI_USELESS) {
        digitalWrite(spi_cs, LOW);
        SPI.transfer(addr | 0x80);
        for(int i = 0; i < size; i++) {
            values[i] = SPI.transfer(0x00);
        }
        digitalWrite(spi_cs, HIGH);
    } else {
        Wire.beginTransmission(i2c_addr);
        Wire.write(addr);
        Wire.endTransmission();
        Wire.requestFrom((int)i2c_addr, (int)size);
        while (Wire.available()) {
            *values = Wire.read();
            values++;
        }
    }
}

uint8_t Pixart_Gesture::readReg(uint8_t addr) {
    uint8_t values;
    readRegs(addr, &values, 1);
    return values;
}

/********************** PAJ7620 Gesture Sensor **********************/

bool paj7620::init()
{   
    spi_cs = GESTURE_SPI_USELESS;
    i2c_addr = PAJ7620_I2C_ADDR;
    Wire.begin();
    delay(10);
    writeReg(0xff, 0x00);
    delay(50);
    /* check ID */
    if((readReg(0x01) != 0x76) || (readReg(0x00) != 0x20))
        return false;
    /* Load the registers data */
    for(uint8_t i = 0; i < INIT_REG_ARRAY_SIZE; i++)
        writeReg(initRegisterArray[i][0], initRegisterArray[i][1]);
    /* Set report mode to Gesture */
    setReportMode(NEAR_240FPS);
    return true;
}

bool paj7620::getResult(paj7620_gesture_t& res)
{
    uint16_t gesture_code;
    gesture_code = (readReg(PAJ7620_REG_RESULT_H)<<8) + readReg(PAJ7620_REG_RESULT_L);
    if (gesture_code == 0) return false;
    for (uint8_t i = UP; i < PAJ7620_GESTURE_COUNT; i++)
    {
        if (gesture_code == (1 << i)) {
            res = (paj7620_gesture_t)i;
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

/********************** PAG7660 Gesture Sensor **********************/

bool pag7660::init(uint8_t cs) {
    spi_cs = cs;
    if(spi_cs != GESTURE_SPI_USELESS) {
        SPI.begin();
        pinMode(spi_cs, OUTPUT);
        digitalWrite(spi_cs, HIGH);
        Serial.println("PAG7660: Use SPI for transfer");
    } else {
        Wire.begin();
    }

    delay(50);
    const uint8_t regs[][2] = {
        { 0x10, 0x04 },        // Set operation to gesture mode
        { 0x22, gestureMode }, // Set gesture mode
        { 0x0A, 0x01 },        // enable cpu
    };
    /* check ID */
    uint16_t id;
    id = (readReg(1) << 8) | readReg(0);
    if (id != 0x7660) {
        Serial.print("check id failed: ");
        Serial.println(id);
        return false;
    }
    /* Load the registers data */
    for (int i = 0; i < sizeof(regs)/2; i++) {
        writeReg(regs[i][0], regs[i][1]);
        delay(10);
    }
    delay(250);
    return true;
}

bool pag7660::getResult(pag7660_gesture_t& res) {
    pag7660_out_t out;
    if (!getOutput(out))
        return false;
    res = out.result;
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

bool pag7660::getOutput(pag7660_out_t& out) {
    /* Check frame ready */
    if (!(readReg(0x04) & 0x02))
        return false;
    /* Read gesture output */
    pag7660_reg_out_t reg;
    readRegs(0x3c, (uint8_t *)&reg, sizeof(reg));
    out = regToOutput(reg);
    /* Clear frame ready */
    writeReg(0x04, 0x00);
    return true;
}

pag7660_out_t pag7660::regToOutput(const pag7660_reg_out_t& reg) {
    pag7660_out_t out;
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
