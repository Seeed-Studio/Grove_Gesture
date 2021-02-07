#include <Wire.h>
#include <paj7620.h>

void setup() {
  Wire.begin();
  //wio link has the power to grove connectors gated by pin 15
  pinMode(15, OUTPUT);
  digitalWrite(15, 1);


  Serial.begin(115200);
  uint8_t errors = paj7620Init(NEAR_GAMING_MODE);
  if (errors) {
    Serial.print("Gesture INIT ERROR,CODE:");
    Serial.println(errors);
  } else {
    Serial.println("INIT OK");
  }

  //might want to do wifi after paj7620 init, it seems to make a difference in how reliably the gesture sensor inits
}

void gotGesture( uint16_t gestureBitField ){
  switch( gestureBitField ){
    case GES_NONE:
      break;
    case GES_RIGHT_FLAG:
      Serial.println("RIGHT");
      break;
    case GES_LEFT_FLAG:
      Serial.println("LEFT");
      break;
    case GES_UP_FLAG:
      Serial.println("UP");
      break;
    case GES_DOWN_FLAG:
      Serial.println("DOWN");
      break;
    case GES_FORWARD_FLAG:
      Serial.println("IN");
      break;
    case GES_BACKWARD_FLAG:
      Serial.println("OUT");
      break;
    case GES_CLOCKWISE_FLAG:
      Serial.println("CW");
      break;
    case GES_COUNT_CLOCKWISE_FLAG:
      Serial.println("CCW");
      break;
    case GES_WAVE_FLAG:
      Serial.println("WAVE");
      break;
    case GES_ERROR:
      Serial.println("GESTURE ERROR");
      break;
  }
}

unsigned long lastGestureCheck = 0;
void loop() {
  if( millis() > lastGestureCheck + 50 ){ //check for a gesture every 50ms
    int gesture = paj7620ReadGesture();
    if( gesture ){ //0 means no gesture, so only print something if we detect a gesture
      gotGesture(gesture);
    }
    lastGestureCheck = millis();
  }
}
