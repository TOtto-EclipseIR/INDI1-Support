TEMPLATE = subdirs

SUBDIRS += \
    apps \
    common \
    libs \

apps.depends = libs
