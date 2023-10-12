#ifndef COMMONEXPORT_H
#define COMMONEXPORT_H

#include "BuildConfig/build_config.h"

#if defined(OS_WIN)

#if defined(COMMON_IMPLEMENTATION)
#define COMMON_EXPORT __declspec(dllexport)
#else
#define COMMON_EXPORT __declspec(dllimport)
#endif // defined(COMMONIMPLEMENTATION)

#else

#if defined(COMMONIMPLEMENTATION)
#define COMMONEXPORT __attribute__((visibility("default")))
#else
#define COMMONEXPORT
#endif

#endif

#endif // COMMONCOMMONEXPORT_H
