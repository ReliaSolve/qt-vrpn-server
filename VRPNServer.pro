QT       += core gui widgets sensors
TARGET = VRPNServer
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11

win32 {
  # Windows wants to compile .C files as if they were .c files, as C.
  # Force the Visual Studio compiler to build as C++ for the VRPN files.
  QMAKE_CFLAGS  += /TP
  # Turn off UNICODE on Windows so we can compile the VRPN files.
  DEFINES -= UNICODE
}

# Pull source files directly from VRPN so we don't need to separately
# compile the library.
#INCLUDEPATH += C:/usr/local/include
#INCLUDEPATH += /usr/local/include
#LIBS += -L"C:/usr/local/lib" -L"/usr/local/lib" -lvrpnserver
INCLUDEPATH += $$PWD/vrpn
SOURCES += \
    vrpn/vrpn_Connection.C \
    vrpn/vrpn_FileConnection.C \
    vrpn/vrpn_Analog.C \
    vrpn/vrpn_Button.C \
    vrpn/vrpn_BaseClass.C \
    vrpn/vrpn_Shared.C \
    vrpn/vrpn_Thread.C \
    vrpn/vrpn_EndpointContainer.C \
    vrpn/vrpn_Serial.C

SOURCES += \
#        GeneralOpenGLWidget.cpp \
        main.cpp \
        mainwindow.cpp

HEADERS += \
#        GeneralOpenGLWidget.h \
        mainwindow.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    android/AndroidManifest.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew.bat \
    android/res/values/libs.xml

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
