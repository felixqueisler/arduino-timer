# arduino-timer
Non-blocking abstracted timer library for use instead of the blocking `delay()`
function. It's relatively low-end, with no callback functions. The timer states
need to be checked manually.

## How to use

1. Include the library with `#include <Q_Timer.h>` at the top of your file
2. Declare and initialize a new Timer instance with `Timer timerName(milliseconds)`
3. Start the timer with `timerName.start()` and optional parameters
4. Check if the timer is ringing with `timerName.isRinging()`
5. If the timer is ringing either `timerName.stop()` or `timerName.restart()`

### Optional: Overflow Compensation
By using `timer.start(0, true)` (only change from 0 if you want to set a custom
starting point) you can activate overflow compensation which can recover over 2
timer intervals to an expected rythm if some blocking code took longer than one
timer interval.

**Rythm example with 1000ms Timers:**

``` NO COMPENSATION
 ┌──┐    ┌───┐   ┌──┐    ┌───────────┐┌─┐     ┌─┐
 │  │    │   │   │  │    │           ││ │     │ │
─┴──┴────┴───┴───┴──┴────┴───────────┴┴─┴─────┴─┴────▶
 0       1       2       3       4       5       6  Seconds
 ┌─────┐ ┌─────┐ ┌─────┐ ┌──────────┐ ┌─────┐ ┌─────┐
 └─────┘ └─────┘ └─────┘ └──────────┘ └─────┘ └─────┘
```

``` COMPENSATING (recovers to expected rythm)
 ┌──┐    ┌───┐   ┌──┐    ┌──────────┐┌─┐ ┌───┐   ┌─┐
 │  │    │   │   │  │    │          ││ │ │   │   │ │
─┴──┴────┴───┴───┴──┴────┴──────────┴┴─┴─┴───┴───┴─┴▶
 0       1       2       3       4       5       6  Seconds
 ┌─────┐ ┌─────┐ ┌─────┐ ┌─────┐ ┌─────┐ ┌─────┐ ┌─────┐
 └─────┘ └─────┘ └─────┘ └─────┘ └─────┘ └─────┘ └─────┘
```

## License

See LICENSE file (GNU GPL v3)
