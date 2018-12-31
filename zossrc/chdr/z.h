#ifndef Z_H
#define Z_H

#if defined(__IBM_METAL__)
#define ATTRIBUTE(mode) __attribute__((mode))
#define PTR32 __ptr32
#else
#define ATTRIBUTE(mode)
#define PTR32
#endif

#endif