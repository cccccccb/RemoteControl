#ifndef BASEEXPORT_H
#define BASEEXPORT_H

#include "BuildConfig/build_config.h"

#if defined(OS_WIN)

#if defined(BASE_IMPLEMENTATION)
#define BASE_EXPORT __declspec(dllexport)
#else
#define BASE_EXPORT __declspec(dllimport)
#endif // defined(BASE_IMPLEMENTATION)

#else

#if defined(BASEIMPLEMENTATION)
#define BASEEXPORT __attribute__((visibility("default")))
#else
#define BASEEXPORT
#endif

#endif

#endif // BASEEXPORT_H
