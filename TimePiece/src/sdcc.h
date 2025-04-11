#ifndef SDCC_H
#define SDCC_H

// Suppress clangd errors
#ifdef CLANGD
#define __asm__() (void)0
#define __critical()
#define __interrupt()
#define __trap
#endif // CLANGD
#endif // SDCC_H
