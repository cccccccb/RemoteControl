SOURCE_QT_BASE_HEADERS += \
    $${_PRO_FILE_PWD_}/application.h            \
    $${_PRO_FILE_PWD_}/locale_loader.h          \
    $${_PRO_FILE_PWD_}/qt_logging.h             \
    $${_PRO_FILE_PWD_}/qt_task_runner.h         \
    $${_PRO_FILE_PWD_}/scoped_qt_logging.h      \

SOURCE_QT_BASE_SOURCES += \
    $${_PRO_FILE_PWD_}/application.cc           \
    $${_PRO_FILE_PWD_}/locale_loader.cc         \
    $${_PRO_FILE_PWD_}/qt_logging.cc            \
    $${_PRO_FILE_PWD_}/qt_task_runner.cc        \

$${upper($${TARGET})}_HEADERS =     \
    $${SOURCE_QT_BASE_HEADERS}

$${upper($${TARGET})}_SOURCES +=    \
    $${SOURCE_QT_BASE_SOURCES}
