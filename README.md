# qt-vrpn-server

This project makes a Qt-based VRPN server to operate on mobile devices.
It exposes the rotational velocity and accelerometer sensors along with
a pose estimated from them.  It also exports some buttons and sliders.

# Building

The project can be opened with QtCreator and configured with the appropriate kit.

To enable the sensors on Android, you need in AndroidManifest.xml of the main application
to add:
    <uses-feature android:name="android.hardware.sensor.accelerometer" />

# Resources

https://doc.qt.io/qtcreator/creator-deploying-android.html

https://doc.qt.io/qt-5/deployment-android.html

https://forum.qt.io/topic/99606/can-not-using-the-qaccelerometer-in-the-android-service
