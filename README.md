# arduino-timer
Non-blocking abstracted timer library for use instead of the blocking `delay()` function.

## How to use
...


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
