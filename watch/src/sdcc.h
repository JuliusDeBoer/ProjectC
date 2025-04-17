#ifndef SDCC_H
#define SDCC_H

// Suppress clangd errors
#if !defined(__SDCC_mcs51)
#define __at(_)
#define __critical(_)
#define __interrupt(_)
#define __trap
#endif
#endif // SDCC_H
