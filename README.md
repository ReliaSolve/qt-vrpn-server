# qt-vrpn-server

This project makes a Qt-based VRPN server to operate on mobile devices.
It exposes the rotational velocity and accelerometer sensors along with
a pose estimated from them.  It also exports some buttons and sliders.

# Building

The project can be opened with QtCreator and configured with the appropriate kit.

To restrict the program to only devices that support its needed features, you can add
lines like the following to the manifest file:
`<uses-feature android:name="android.hardware.sensor.accelerometer" />`
This will cause the program only to be offered on the Play Store to devices with
those features.

# Resources

https://doc.qt.io/qtcreator/creator-deploying-android.html

https://doc.qt.io/qt-5/deployment-android.html

https://forum.qt.io/topic/99606/can-not-using-the-qaccelerometer-in-the-android-service
