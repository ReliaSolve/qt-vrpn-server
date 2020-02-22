#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

signals:
    void displayText(QString text);

private:
    Ui::MainWindow *ui;

    void DisplayState();
    QString m_displayText;

    bool m_button0 = false;
    bool m_button1 = false;
    bool m_button2 = false;

    double m_analog0 = 0;
    double m_analog1 = 0;
};

#endif // MAINWINDOW_H
