TEMPLATE = subdirs

SUBDIRS +=  \
    Base    \
    Common  \
    QtBase  \
    Others  \
    Proto   \
    Client  \
    Host    \

Base.depends = Others Proto
Common.depends = Base QtBase
Client.depends = Common
Host.depends = Common QtBase
