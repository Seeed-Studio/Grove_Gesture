/*
    Copyright (c) 2023 seeed technology inc.
    Website    : www.seeed.cc
    Author     : Wuruibin
    Modified Time: June 2023
    Description: This demo can recognize 15 gestures and output the result.
  				You can adjust the reaction time according to the actual circumstance
 				by modifying "#define GES_REACTION_TIME  500".

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

/*
    Notice: When you want to recognize the Forward/Backward gesture or other continuous gestures, your gestures' reaction time must less than GES_REACTION_TIME(0.8s).
        You also can adjust the reaction time according to the actual circumstance.
*/
#define GES_REACTION_TIME		800
#define GES_QUIT_TIME			1000

paj7620 Gesture;

void setup() {
    Serial.begin(9600);
    while(!Serial) {
        delay(100);
    }
    Serial.println("\nPAJ7620U2 TEST DEMO: Recognize 15 gestures.");
    
    if(Gesture.init()) {
        Serial.println("PAJ7620U2 initialization failed");
    } else {
        Serial.println("PAJ7620U2 initialization success");
    }
    Serial.println("Please input your gestures:\n");
}

void loop() {
    paj7620_gesture_t result;
    if (Gesture.getResult(result)) {
        switch (result) {
        case RIGHT:
            delay(GES_REACTION_TIME);
            Gesture.getResult(result);
            if (result == LEFT) {
                Serial.println("Right-Left");
            } else if (result == PUSH) {
                Serial.println("Forward");
                delay(GES_QUIT_TIME);
            } else if (result == POLL) {
                Serial.println("Backward");
                delay(GES_QUIT_TIME);
            } else {
                Serial.println("Right");
            }
            break;
        case LEFT:
            delay(GES_REACTION_TIME);
            Gesture.getResult(result);
            if (result == RIGHT) {
                Serial.println("Left-Right");
            } else if (result == PUSH) {
                Serial.println("Forward");
                delay(GES_QUIT_TIME);
            } else if (result == POLL) {
                Serial.println("Backward");
                delay(GES_QUIT_TIME);
            } else {
                Serial.println("Left");
            }
            break;
        case UP:
            delay(GES_REACTION_TIME);
            Gesture.getResult(result);
            if (result == DOWN) {
                Serial.println("Up-Down");
            } else if (result == PUSH) {
                Serial.println("Forward");
                delay(GES_QUIT_TIME);
            } else if (result == POLL) {
                Serial.println("Backward");
                delay(GES_QUIT_TIME);
            } else {
                Serial.println("Up");
            }
            break;
        case DOWN:
            delay(GES_REACTION_TIME);
            Gesture.getResult(result);
            if (result == UP) {
                Serial.println("Down-Up");
            } else if (result == PUSH) {
                Serial.println("Forward");
                delay(GES_QUIT_TIME);
            } else if (result == POLL) {
                Serial.println("Backward");
                delay(GES_QUIT_TIME);
            } else {
                Serial.println("Down");
            }
            break;
        case PUSH:
            delay(GES_REACTION_TIME);
            Gesture.getResult(result);
            if (result == POLL) {
                Serial.println("Forward-Backward");
                delay(GES_QUIT_TIME);
            } else {
                Serial.println("Forward");
                delay(GES_QUIT_TIME);
            }
            break;
        case POLL:
            delay(GES_REACTION_TIME);
            Gesture.getResult(result);
            if (result == PUSH) {
                Serial.println("Backward-Forward");
                delay(GES_QUIT_TIME);
            } else {
                Serial.println("Backward");
                delay(GES_QUIT_TIME);
            }
            break;
        case CLOCKWISE:
            Serial.println("Clockwise");
            break;
        case ANTI_CLOCKWISE:
            Serial.println("anti-clockwise");
            break;
        case WAVE:
            Serial.println("wave");
            break;
        default:
            break;
        }
    }
    delay(100);
}

