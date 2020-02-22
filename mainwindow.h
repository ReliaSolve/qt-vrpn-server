#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
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

signals:
    void displayText(QString text);

private:
    Ui::MainWindow *ui;

    // Local state
    void DisplayState();
    QString m_displayText;
    QString m_statusText;

    bool m_button0 = false;
    bool m_button1 = false;
    bool m_button2 = false;

    double m_analog0 = 0;
    double m_analog1 = 0;

    // VRPN objects
    vrpn_Connection *m_connection = nullptr;
    vrpn_Button_Server *m_buttons = nullptr;
    vrpn_Analog_Server *m_analogs = nullptr;

    // Periodic updates
    QTimer *m_timer = nullptr;
};

#endif // MAINWINDOW_H
