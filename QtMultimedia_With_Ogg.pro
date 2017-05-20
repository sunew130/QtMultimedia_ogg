# Made By Jiangcaiyang at 19时40分17秒 2013年1月19日

TARGET   = QtMultOgg
QT       -= gui
QT       += multimedia core
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app


INCLUDEPATH         += $${_PRO_FILE_PWD_}
HEADERS += \
    QOggVorbis.h

SOURCES += \
    main.cpp \
    QOggVorbis.cpp

unix {# 适用于Unix/Linux的
LIBS += $${_PRO_FILE_PWD_}/libVorbisFile_X11.a \
        $${_PRO_FILE_PWD_}/libVorbis_X11.a \
        $${_PRO_FILE_PWD_}/libOgg_X11.a
}
win32 {# 适用于Windows的
LIBS += $${_PRO_FILE_PWD_}/libVorbisFile_win32.a \
        $${_PRO_FILE_PWD_}/libVorbis_win32.a \
        $${_PRO_FILE_PWD_}/libOgg_win32.a
}
