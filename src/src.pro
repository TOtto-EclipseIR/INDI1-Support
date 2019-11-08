TEMPLATE = subdirs

SUBDIRS += \
    apps \
    libs \

apps.depends = libs
