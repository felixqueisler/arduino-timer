/* Q_Timer.h - Library providing non-blocking timers for "async" events.
 *
 * Copyright (c) 2018 Felix Queisler
 *
 * License GNU GPL v3
 */

#ifndef Q_Timer_h
#define Q_Timer_h

#define COMPENSATE_OVERFLOW 1

#include "Arduino.h"

class Timer {
public:
  /* Timer Constructor
   * Sets compensate_overflow to off/false
   *
   * param length: Sets the time in milliseconds required for the timer to go *
   * off
   */
  Timer(unsigned long length); // ms

  /* Starts the timer now
   */
  void start();

  /* Starts the timer
   *
   * param start_time: Sets a starting point in the past or future in ms from
   * the start of the microcontroller. 0 will default to current millis()
   */
  void start(unsigned long start_time);

  /* Enables optional features. Should be called before starting the timer to
   * avoid unexpected behaviour.
   *
   * param feature: Takes Macros defined at the top of this file
   */
  void enable(int feature);

  /* Disables optional features. Should be called before starting the timer to
   * avoid unexpected behaviour.
   *
   * param feature: Takes Macros defined at the top of this file
   */
  void disable(int feature);

  /* Pause the timer and remember the already elapsed time for when you
   * unpause through timer.start() again
   */
  void pause(); // save the already elapsed time and pause

  /* Stops/Resets the timer and forgets the already elapsed time.
   * The timer doesn't restart automatically.
   */
  void stop();

  /* Updates the variables, most importantly whether the timer is ringing
   */
  void update();

  /* Turns off the ringing and restarts the timer
   */
  void restart();

  /* Returns whether the timer is ringing because enough time has passed
   */
  bool isRinging();

  /* Returns whether the timer is running at all
   */
  bool isRunning();

private:
  bool running;                  // Enables/Disables the timer
  bool ringing;                  // Times' up!
  unsigned long ringing_counter; // Number of ringing occurences

  bool compensate_overflow;
  unsigned long interval_time; // Timer rings every <interval_timer> ms
  unsigned long starting_point;    // this & interval_time result in the next ring
  unsigned long elapsed;
};

#endif
