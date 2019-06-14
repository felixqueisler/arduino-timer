/* Q_Timer.cpp - Library providing non-blocking timers for "async" events.
 *
 * Copyright (c) 2018 Felix Queisler
 *
 * License GNU GPL v3
 */

#include "Q_Timer.h"

Timer::Timer(unsigned long length) {
  this->running = false;
  this->ringing = false;
  this->ringing_counter = 0;
  this->interval_time = length;
  this->starting_point = 0;
  this->elapsed = 0;
  this->compensate_overflow = false;
}

void Timer::start() {
  unsigned long now = millis();

  if (this->elapsed > 0)
    this->starting_point = now - this->elapsed;
  else
    this->starting_point = now;

  this->elapsed = 0;
  this->running = true;
}

void Timer::start(unsigned long start_time) {
  unsigned long now = millis();

  if (start_time > 0)
    this->starting_point = now - start_time;
  else if (this->elapsed > 0)
    this->starting_point = now - this->elapsed;
  else
    this->starting_point = now;

  this->elapsed = 0;
  this->running = true;
}

void Timer::enable(int feature) {
  switch (feature) {
  case COMPENSATE_OVERFLOW:
    this->compensate_overflow = true;
    break;
  }
}

void Timer::disable(int feature) {
  switch (feature) {
  case COMPENSATE_OVERFLOW:
    this->compensate_overflow = false;
    break;
  }
}

void Timer::pause() {
  this->running = false;
  this->ringing = false;
  this->elapsed = millis() - this->starting_point;
}

void Timer::stop() {
  this->running = false;
  this->ringing = false;
  this->elapsed = 0;
}

void Timer::update() {
  if (this->running == true && this->ringing == false) {
    if ((millis() - this->starting_point) > this->interval_time) {
      this->ringing = true;
      this->ringing_counter++;
    }
  }
}

void Timer::restart() {
  this->ringing = false;

  if (compensate_overflow == true) {
    // Sets the correct starting_point as if the Timer was restarted in rythm
    this->starting_point = this->starting_point + this->interval_time;
  } else {
    // Doesn't care
    this->starting_point = millis();
  }
}

bool Timer::isRinging() {
  this->update();
  return this->ringing;
}

bool Timer::isRunning() { return this->running; }
