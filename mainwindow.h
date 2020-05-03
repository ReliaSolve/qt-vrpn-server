#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QSensor>
#include <QGyroscope>
#include <QAccelerometer>
#include <vrpn_Connection.h>
#include <vrpn_Analog.h>
#include <vrpn_Button.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void Button0Down();
    void Button0Up();
    void Button1Down();
    void Button1Up();
    void Button2(bool state);

    void Analog0(int percent);
    void Analog1(int percent);

protected slots:
    void Update();
    void HandleGyro();
    void HandleAccel();

signals:
    void displayText(QString text);

private:
    Ui::MainWindow *ui;

    // Local state
    void DisplayState();
    QString m_displayText;
    QString m_statusText;

    // First three buttons of the Button0 device
    bool m_button0 = false;
    bool m_button1 = false;
    bool m_button2 = false;

    // Analogs 6 and 7 from the Analog0 device
    double m_analog0 = 0;
    double m_analog1 = 0;

    // VRPN objects
    vrpn_Connection *m_connection = nullptr;
    vrpn_Button_Server *m_buttons = nullptr;
    vrpn_Analog_Server *m_analogs = nullptr;

    // Sensors we can read from the device
    QGyroscope *m_gyro = nullptr;
    QAccelerometer *m_accel = nullptr;

    // Periodic updates
    QTimer *m_timer = nullptr;
};

#endif // MAINWINDOW_H
