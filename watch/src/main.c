#include "sdcc.h"

// TIM2 control register 1
volatile unsigned char __at(0x005300) TIM2_CR1;
// TIM2 Interrupt enable register
volatile unsigned char __at(0x005301) TIM2_IER;
// TIM2 status register 1
volatile unsigned char __at(0x005301) TIM2_SR1;
//  TIM2 capture/compare mode register 1
volatile unsigned char __at(0x005305) TIM2_CCMR1;
// TIM2 capture/compare enable register 1
volatile unsigned char __at(0x005308) TIM2_CCER1;
// TIM2 prescaler register
volatile unsigned char __at(0x00530C) TIM2_PSCR;
// TIM2 auto-reload register high
volatile unsigned char __at(0x00530D) TIM2_ARRH;
// TIM2 auto-reload register low
volatile unsigned char __at(0x00530E) TIM2_ARRL;
// TIM2 capture/compare register 1 high
volatile unsigned char __at(0x00530F) TIM2_CCR1H;
// TIM2 capture/compare register 1 low
volatile unsigned char __at(0x005310) TIM2_CCR1L;

typedef enum {
  WATCH_SCREEN,
} Screen;

typedef struct {
  // NOTE(Julius): Somewhere there will probaby appear an error. But for now
  //               its just an 8 bit int. :)
  unsigned char hour;
  unsigned char minute;
  unsigned char second;
  Screen currentScreen;
} WatchData;

volatile WatchData WATCH_DATA = {
    .hour = 0,
    .minute = 0,
    .second = 0,
    .currentScreen = WATCH_SCREEN,
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

void updateDisplay(void) {
  // TODO(Julius)
}

void tim2Compare(void) __interrupt(14 /* TIM2 capture/compare */) {
  // TIM2_SR1 ^ 0x01
  if (!(TIM2_SR1 & 0x01)) {
    return;
  }

  advanceTime();

  if (WATCH_DATA.currentScreen == WATCH_SCREEN) {
    updateDisplay();
  }

  // Clear the interrupt flag?
  TIM2_SR1 &= ~0x01;
}

inline void enableTim2interrupt(void) {
  TIM2_CR1 = 0x01;

  // Set auto reload registers
  // TODO(Julius): These values are probably wrong.
  TIM2_PSCR = 0x08; // 256
  // 62,499
  TIM2_ARRH = 0xF3;
  TIM2_ARRL = 0xAB;

  // Set capture/compare register
  TIM2_CCR1H = 0x00;
  TIM2_CCR1L = 0x78;

  // Something something compare mode
  TIM2_CCMR1 = 0x30;

  // Enable output?
  TIM2_CCER1 = 0x01;

  // Enable the interrupt
  TIM2_IER = 0x01;
}

void main(void) {
  enableTim2interrupt();

  for (;;) {
    __asm__("nop");
  }
}