TEMPLATE = subdirs

SUBDIRS +=  \
    Core    \
    Agent   \
    Main    \
    Service \

Service.depends = Core
Main.depends = Core
Agent.depends = Core
