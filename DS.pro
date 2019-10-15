TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    object.cpp \
    exception.cpp \
    dstring.cpp

HEADERS += \
    smartpointer.h \
    object.h \
    exception.h \
    list.h \
    seqlist.h \
    staticlist.h \
    dynamiclist.h \
    array.h \
    staticarray.h \
    dynamicarray.h \
    linklist.h \
    dynamiclinklist.h \
    circlelist.h \
    duallinklist.h \
    stack.h \
    staticstack.h \
    linkstack.h \
    queue.h \
    staticqueue.h \
    linkqueue.h \
    dstring.h \
    sort.h \
    tree.h \
    treenode.h \
    pointer.h \
    sharedpointer.h
