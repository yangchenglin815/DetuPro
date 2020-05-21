#-------------------------------------------------
#
# Project created by QtCreator 2017-06-07T09:40:17
#
#-------------------------------------------------

QT       += core gui multimedia multimediawidgets opengl
DEFINES += _USE_MATH_DEFINES
RC_FILE += DetuMonitor.rc 
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

INCLUDEPATH += ../../../depano-dependencies/boost/1580/include
INCLUDEPATH += ../../../depano-dependencies/include
INCLUDEPATH += ../../../depano-dependencies/include/LibGLStitch
INCLUDEPATH += ../../../depano-dependencies/include/M1Api
INCLUDEPATH += ../../../dem1service/dem1service
INCLUDEPATH += /Dependency/include
INCLUDEPATH += /Dependency/QtAV/include

unix|win32: LIBS += -L$$PWD/../../../depano-dependencies/boost/1580/x64/vc120/lib
unix|win32: LIBS += -L$$PWD/../../../depano-dependencies/lib

TARGET = DetuPVMS
TEMPLATE = app
#LIBS +=avutil.lib avformat.lib avfilter.lib avdevice.lib avcodec.lib opengl32.lib glu32.lib LibGlStitch.lib stitchLib.lib dem1service.lib


SOURCES += main.cpp\
        DetuPVMS.cpp \
    logging.cpp \
    FramelessWidget.cpp \
    FlvParser.cpp \
    StitchThreadPool.cpp \
    detuTittleWgt.cpp \
    homeWgt.cpp \
    consoleWgt.cpp \
    commonPageWgt.cpp

HEADERS  += DetuPVMS.h \
    panoutil.h \
    c99defs.h \
    circlebuf.h \
    darray.h \
    logging.h \
    util_uint128.h \
    FramelessWidget.h \
    AudioVideoConfig.h \
    concurrentqueue.h \
    ffmpeg.h \
    FLvParser.h \
    locking_queue.h \
    StitchThreadPool.h \
    media.h \
    detuTittleWgt.h \
    homeWgt.h \
    consoleWgt.h \
    commonPageWgt.h

FORMS    += DetuPVMS.ui \
    detuTittleWgt.ui \
    homeWgt.ui \
    consoleWgt.ui \
    commonPageWgt.ui

RESOURCES += \
    detupvms.qrc

INCLUDEPATH += $$PWD/../../../depano-dependencies/include
DEPENDPATH += $$PWD/../../../depano-dependencies/include

unix|win32: LIBS += -L$$PWD/../../../library/build/opencv/249/lib/ -lopencv_core249

INCLUDEPATH += $$PWD/../../../library/build/opencv/249/include
DEPENDPATH += $$PWD/../../../library/build/opencv/249/include

unix|win32: LIBS += -L$$PWD/../../../library/build/opencv/249/lib/ -lopencv_imgproc249

INCLUDEPATH += $$PWD/../../../library/build/opencv/249/include
DEPENDPATH += $$PWD/../../../library/build/opencv/249/include

unix|win32: LIBS += -L$$PWD/../../../library/build/opencv/249/lib/ -lopencv_highgui249

INCLUDEPATH += $$PWD/../../../library/build/opencv/249/include
DEPENDPATH += $$PWD/../../../library/build/opencv/249/include

QMAKE_CXXFLAGS +=
