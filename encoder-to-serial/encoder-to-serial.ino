
#include <Arduino.h>
#include <RotaryEncoder.h>

#define PIN_IN1 6
#define PIN_IN2 5

#define ROTARYMAX 1600

RotaryEncoder encoder(PIN_IN1, PIN_IN2, RotaryEncoder::LatchMode::TWO03);

int lastPos = -1;

void setup()
{
  Serial.begin(115200);
  while (! Serial);

  encoder.setPosition(0);
}


void loop()
{
  encoder.tick();

  // get the current physical position and calc the logical position
  int newPos = encoder.getPosition() ;

  if (lastPos != newPos) {
    lastPos = newPos % ROTARYMAX;

    if (lastPos < 0 ) {
      lastPos  = ROTARYMAX + lastPos;
    }
    encoder.setPosition(lastPos);

    Serial.print(lastPos );
    Serial.println();
  }
}
