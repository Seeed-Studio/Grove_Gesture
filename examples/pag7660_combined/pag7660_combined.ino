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
    Serial.println("\nPAG7660 TEST DEMO: Gesture combined mode.");
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
        Serial.println(getResultCombinedMode(result));
    }
}

char* getResultCombinedMode(const pag7660_gesture_t& result) {
    char _result_str[32];
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
                strcpy(_result_str, cursor_str[result.cursor.type]);
            break;
        default:
            strcpy(_result_str, "");
            break;
        }
        break;
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
        sprintf(_result_str, "%d-finger", result.type);
        break;
    case 6:
        sprintf(_result_str, "Rotate Right %d", result.rotate);
        break;
    case 7:
        sprintf(_result_str, "Rotate Left %d", result.rotate);
        break;
    case 8:
        strcpy(_result_str, "Swipe Left");
        break;
    case 9:
        strcpy(_result_str, "Swipe Right");
        break;
    case 19:
    case 20:
    case 21:
    case 22:
    case 23:
        sprintf(_result_str, "%d-finger push", result.type - 19 + 1);
        break;
    default:
        strcpy(_result_str, "");
        break;
    }
    return _result_str;
}