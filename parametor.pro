#-------------------------------------------------
#
# Project created by QtCreator 2013-06-11T20:48:11
#
#-------------------------------------------------
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Parametor
TEMPLATE = app
RC_FILE = parametor.rc
QT += svg charts
INCLUDEPATH += ./src/

macx {
    #APP_BUNDLE_FILES.files = torus_input_definitions.xml
    #APP_BUNDLE_FILES.path = Contents/Resources
    #QMAKE_BUNDLE_DATA += APP_BUNDLE_FILES
    QMAKE_INFO_PLIST = Info.plist
    ICON = ParametorIcon.icns

    #Qwt libraries for Mac OS X
    LIBS += -framework qwt
    CONFIG += qwt
}

win32 {
    CONFIG(debug, debug|release) {
        LIBS += -LC:\Qwt-6.1.0\lib -lqwtd
    } else {
        LIBS += -LC:\Qwt-6.1.0\lib -lqwt
    }
    INCLUDEPATH += C:\Qwt-6.1.0\include
    CONFIG += qwt
}

SOURCES += \
        ./src/main.cpp\
        ./src/mainwindow.cpp \
        ./src/pparameterdata.cpp \
        ./src/psourcedata.cpp \
        ./src/pimagedata.cpp \
        ./src/panglegen.cpp \
        ./src/torusconsole.cpp \
        ./src/unitconverter.cpp \
        ./src/pparameterdefinition.cpp \
        ./src/pdustdata.cpp \
        ./src/ptorusupdatewidget.cpp \
        ./src/paboutdialog.cpp \
        ./src/pcompileconfiguredialog.cpp \
        ./src/ptorusmonitor.cpp \
        ./src/psedplotter.cpp

HEADERS  += \
        ./src/mainwindow.h \
    	./src/pparameterdata.h \
        ./src/psourcedata.h \
        ./src/pimagedata.h \
        ./src/panglegen.h \
        ./src/torusconsole.h \
        ./src/unitconverter.h \
        ./src/pparameterdefinition.h \
        ./src/pdustdata.h \
        ./src/ptorusupdatewidget.h \
        ./src/paboutdialog.h \
        ./src/pcompileconfiguredialog.h \
        ./src/ptorusmonitor.h \
        ./src/psedplotter.h

FORMS    += \
        ./ui/mainwindow.ui \
        ./ui/panglegen.ui \
        ./ui/torusconsole.ui \
        ./ui/unitconverter.ui \
        ./ui/ptorusupdatewidget.ui \
        ./ui/paboutdialog.ui \
        ./ui/ptorusmonitor.ui \
        ./ui/psedplotter.ui

RESOURCES += \
    Resources.qrc

