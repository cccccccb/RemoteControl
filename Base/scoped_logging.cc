#include "Base/scoped_logging.h"

namespace base {

ScopedLogging::ScopedLogging(const LoggingSettings &settings)
{
    initialized_ = initLogging(settings);
}

ScopedLogging::~ScopedLogging()
{
    if (initialized_)
        shutdownLogging();
}

}
