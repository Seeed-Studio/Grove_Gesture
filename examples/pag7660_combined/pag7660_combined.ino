/*
    Copyright (c) 2023 seeed technology inc.
    Website    : www.seeed.cc
    Author     : JX.Weng
    Modified Time: June 2023
    Description: Get the pag7660 recognition result in combined mode.

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

pag7660 Gesture; // Combined mode is used by default

void setup() {
    Serial.begin(9600);
    while(!Serial) {
        delay(100);
    }
    Serial.println("\nPAG7660 TEST DEMO: Gesture combined mode.");
    
    if(Gesture.init()) {
        Serial.println("PAG7660 initialization success");
    } else {
        Serial.println("PAG7660 initialization failed");
    }
    Serial.println("Please input your gestures:\n");
}

void loop() {
    pag7660_gesture_t result;
    if (Gesture.getResult(result)) {
        printResultCombinedMode(result);
    }
    delay(100);
}

void printResultCombinedMode(const pag7660_gesture_t& result) {
    const char *cursor_str[] = {
        NULL,
        "Tap",
        "Grab",
        "Pinch",
    };
    switch (result.type) {
    case 0:
        switch (result.cursor.type) {
        case 1:
        case 2:
        case 3:
            if (result.cursor.select)
                Serial.println(cursor_str[result.cursor.type]);
            break;
        default:
            break;
        }
        break;
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
        Serial.print(result.type);
        Serial.println("-finger");
        break;
    case 6:
        Serial.print("Rotate Right ");
        Serial.println(result.rotate);
        break;
    case 7:
        Serial.print("Rotate Left ");
        Serial.println(result.rotate);
        break;
    case 8:
        Serial.println("Swipe Left");
        break;
    case 9:
        Serial.println("Swipe Right");
        break;
    case 19:
    case 20:
    case 21:
    case 22:
    case 23:
        Serial.print(result.type - 19 + 1);
        Serial.println("-finger push");
        break;
    default:
        break;
    }
}