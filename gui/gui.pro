SOURCES += \
    main.cpp \
    App.cpp \
    setusername.cpp \
    ../cJSON.cpp \
    ../Json.cpp \
    ../lm_autolock.cpp \
    userlist.cpp \
    chatwnd.cpp
QT += widgets gui network
CONFIG += C++11

HEADERS += \
    App.h \
    setusername.h \
    ../lm_def.h \
    ../Json.h \
    ../lm_autolock.h \
    ../lm_public.h \
    ../socket.h \
    ../cJSON.h \
    userlist.h \
    chatwnd.h

RESOURCES += \
    src.qrc

FORMS += \
    setusername.ui \
    userlist.ui \
    chatwnd.ui
