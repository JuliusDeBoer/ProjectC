#include "sdcc.h"

typedef struct {
  // NOTE(Julius): God I with there were smaller ints
  unsigned int hour;
  unsigned int minute;
  unsigned int second;
} WatchData;

volatile WatchData WATCH_DATA = {
    .hour = 0,
    .minute = 0,
    .second = 0,
};

/**
 * This function is tasked with the very important job of advancing time. Good
 * to know that this heavy task is handled in C. :)
 *
 * The function modifies the global WATCH_DATA structure directly.
 */
inline void advanceTime(void) {
  WATCH_DATA.second++;
  if (WATCH_DATA.second < 60) {
    return;
  }

  WATCH_DATA.second = 0;
  WATCH_DATA.minute++;

  if (WATCH_DATA.minute < 60) {
    return;
  }

  WATCH_DATA.minute = 0;
  WATCH_DATA.hour++;

  if (WATCH_DATA.hour < 24) {
    return;
  }

  WATCH_DATA.hour = 0;
}

inline void updateDisplay(void) {
    // TODO(Julius)
}

void tim2Compare(void) __interrupt(14 /* TIM2 capture/compare */) {
  __asm__("; Cool inline asm!"
          "nop");
  advanceTime();
  updateDisplay();
}

void main(void) {}