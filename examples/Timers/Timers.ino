/* Arduino Timer Example
 *
 * Simple example of the timer library. Shows most of it's features and
 * its capability to have multiple instances for multiple "async" events.
 *
 * Copyright (c) 2018 Felix Queisler
 *
 * License GNU GPL v3
*/

#include <Q_Timer.h>

Timer ledTimer(500); // create a new instance with desired countdown in ms
Timer serialTimer(2000); // 2nd timer for serial

int counter = 0;

void setup() {
  Serial.begin(115200);
  ledTimer.start();
  serialTimer.enable(COMPENSATE_OVERFLOW);  // Activates compensation of timer
                                            // overflow to always report at
                                            // least once per 2000 ms
  serialTimer.start();
}

void loop () {
  if (ledTimer.isRinging()) {
    // Blink the LED on and off
    if (digitalRead (LED_BUILTIN) == LOW) digitalWrite(LED_BUILTIN, HIGH);
    else digitalWrite(LED_BUILTIN, LOW);

    Serial.print("LED ");
    int randNumber = random(10, 20);
    Serial.println(randNumber);

    counter++;
    ledTimer.restart();
  }

  if (serialTimer.isRinging()) {
    Serial.println("Serial Timer ding ding ding");
    serialTimer.restart();
  }

  if (counter > 20 && ledTimer.isRunning()) { // 10 seconds in
    ledTimer.stop();
    delay(3000); // To proof that serialTimer is compensating for delays
  }

  if (ledTimer.isRunning() == false) {
    digitalWrite(LED_BUILTIN, LOW); // Finally turn off LED
  }
}
