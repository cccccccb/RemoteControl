#ifndef CLIENT_CORE_EXPORT_H
#define CLIENT_CORE_EXPORT_H

#include "BuildConfig/build_config.h"

#if defined(OS_WIN)

#if defined(CLIENT_CORE_IMPLEMENTATION)
#define CLIENT_CORE__EXPORT __declspec(dllexport)
#else
#define CLIENT_CORE__EXPORT __declspec(dllimport)
#endif // defined(CLIENT_CORE_IMPLEMENTATION)

#else

#if defined(CLIENTCOREIMPLEMENTATION)
#define CLIENT_CORE_EXPORT __attribute__((visibility("default")))
#else
#define CLIENT_CORE_EXPORT
#endif

#endif

#endif // CLIENT_CORE_EXPORT_H
