/*
    Copyright (c) 2023 seeed technology inc.
    Website    : www.seeed.cc
    Author     : JX.Weng
    Modified Time: June 2023
    Description: Get the pag7660 recognition result in thumb mode.

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

pag7660 Gesture(GESTURE_THUMB_MODE); // Thumb mode is used

void setup() {
    Serial.begin(9600);
    Serial.println("\nPAG7660 TEST DEMO: Gesture thumb mode.");
    if(Gesture.init()) {
        Serial.println("PAG7660 initialization failed");
    } else {
        Serial.println("PAG7660 initialization success");
    }
    Serial.println("Please put your hand in front of sensor:\n");
}

void loop() {
    pag7660_gesture_t result;
    if (Gesture.getResult(result)) {
        Serial.print("Gesture: ");
        Serial.println(getResultThumbMode(result));
    }
}

char* getResultThumbMode(const pag7660_gesture_t& result) {
    char _result_str[32];
    if (result.thumb.up)
        sprintf(_result_str, "Thumb Up");
    else if (result.thumb.down)
        sprintf(_result_str, "Thumb Down");
    return _result_str;
}