TEMPLATE = subdirs

SUBDIRS += \
    base \
    core \
    exe \
    gui \
    widget \

core.depends = base

