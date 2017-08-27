TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    posixmq.cpp \
    semaphore.cpp \
    psxsem.cpp \
    sysvshmem.cpp
