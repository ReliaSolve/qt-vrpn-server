# qt-vrpn-server

This project makes a Qt-based VRPN server to operate across platforms,
including on mobile devices.
It exposes the rotational velocity and accelerometer sensors 
on device that have them.  It also exports some buttons and sliders on all
platforms.

# Building

The project can be opened with QtCreator and configured with the appropriate kit.

To restrict the program to only Android devices that support its needed features, you can add
lines like the following to the manifest file:
`<uses-feature android:name="android.hardware.sensor.accelerometer" />`
This will cause the program only to be offered on the Play Store to devices with
those features.  This is not needed because the program responds differently when
it does not find the sensors so is able to run across devices.

# Qt Sensors on Android

The Android Sensors do not work with Qt 5.14 because of an incorrect naming of the sensor DLLs which keeps them from being linked correctly.

It does work with Qt 5.12.7.

# Resources

https://doc.qt.io/qtcreator/creator-deploying-android.html

https://doc.qt.io/qt-5/deployment-android.html

https://forum.qt.io/topic/111388/problem-with-qmagnetometer-et-qaccelerometer-under-qt-5-14-1-and-android

