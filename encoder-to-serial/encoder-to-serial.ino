
#include <Arduino.h>
#include <RotaryEncoder.h>

#define PIN_IN1 6
#define PIN_IN2 5

#define ROTARYMAX 1600

RotaryEncoder encoder(PIN_IN1, PIN_IN2, RotaryEncoder::LatchMode::TWO03);

int lastPos = -1;



#define stepperPulsePin 9 // green
#define stepperDirectionPin 10 // white
#define stepperEnablePin 11 // blue

volatile boolean stepper_direction = LOW;
volatile boolean steper_pulse_state = LOW;

volatile boolean run_mode = LOW;

volatile int counter = 0;


void setup()
{
  Serial.begin(115200);
  while (! Serial);

  encoder.setPosition(0);

  cli();
  TCCR0A = 0;// set entire TCCR0A register to 0
  TCCR0B = 0;// same for TCCR0B
  TCNT0  = 0;//initialize counter value to 0
  OCR0A = 124;// = (16*10^6) / (2000*64) - 1 (must be <256)
  TCCR0A |= (1 << WGM01);
  TCCR0B |= (1 << CS01) | (1 << CS00);
  TIMSK0 |= (1 << OCIE0A);

  pinMode(stepperPulsePin, OUTPUT);
  pinMode(stepperDirectionPin, OUTPUT);
  pinMode(stepperEnablePin, OUTPUT);

  sei();

  digitalWrite(stepperEnablePin, run_mode);
  digitalWrite(stepperDirectionPin, LOW);
  digitalWrite(stepperPulsePin, LOW);
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


ISR(TIMER0_COMPA_vect) { //timer0 interrupt 2kHz toggles pin 8
  steper_pulse_state = !steper_pulse_state;
  digitalWrite(stepperDirectionPin, HIGH);
  digitalWrite(stepperPulsePin, steper_pulse_state);
  digitalWrite(stepperEnablePin, run_mode);
  counter ++;
  if (counter > 2000) {
    run_mode = !run_mode;
    counter = 0;
  }
}
