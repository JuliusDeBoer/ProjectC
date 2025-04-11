#include "sdcc.h"

void tim2Compare(void) __interrupt(14 /* TIM2 capture/compare */) {
  __asm__("; Cool inline asm!"
          "nop");
}

void main(void) {}
