
//Includes the Arduino Stepper Library
#include <Stepper.h>
#include <IRremote.hpp>

// Defines the number of steps per rotation
#define STEPS_PER_REVOLUTION 2038
#define RECV_PIN 7

// Creates an instance of stepper class
// Pins entered in sequence IN1-IN3-IN2-IN4 for proper step sequence
Stepper myStepper = Stepper(STEPS_PER_REVOLUTION, 5, 3, 4, 2);

IRrecv irrecv(RECV_PIN);
decode_results results;

void setup() {
	// Nothing to do (Stepper Library sets pins as outputs)
  Serial.begin(9600);
  irrecv.enableIRIn();
}

void loop() {
	myStepper.setSpeed(20);

	// Rotate CW slowly at 5 RPM
	// myStepper.step(STEPS_PER_REVOLUTION * 25);

  if (irrecv.decode(&results)) {
    if (results.value == 0xFFA25D) {
      myStepper.step(STEPS_PER_REVOLUTION * 2);
    }
    Serial.println(results.value, HEX);
    irrecv.resume(); // Receive the next value
  }
}