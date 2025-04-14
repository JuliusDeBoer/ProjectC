#ifndef SDCC_H
#define SDCC_H

// Suppress clangd errors
#ifdef CLANGD
#define NULL #define __asm__(_)(void) 0
#define __critical(_)
#define __interrupt(_)
#define __trap
#endif // CLANGD
#endif // SDCC_H
