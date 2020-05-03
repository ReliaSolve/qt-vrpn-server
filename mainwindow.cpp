#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtNetwork/QtNetwork>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Report the version of the program
    m_statusText += "Version: " + m_version + "\n";

    // Get my IP address so the client will know where to connect
    m_statusText += "Network interfaces:";
    QList<QHostAddress> list = QNetworkInterface::allAddresses();
    for(int nIter=0; nIter<list.count(); nIter++) {
      if(!list[nIter].isLoopback()) {
          if (list[nIter].protocol() == QAbstractSocket::IPv4Protocol ) {
              m_statusText += " " + list[nIter].toString();
          }
      }
    }
    m_statusText += "\n";

    // Start up all of the sensors we might have and set handlers for their values.
    m_gyro = new QGyroscope(this);
    connect(m_gyro, SIGNAL(readingChanged()), this, SLOT(HandleGyro()));
    m_gyro->setActive(true);
    if (!m_gyro->start()) {
        delete m_gyro;
        m_gyro = nullptr;
    }

    m_accel = new QAccelerometer(this);
    connect(m_accel, SIGNAL(readingChanged()), this, SLOT(HandleAccel()));
    m_accel->setActive(true);
    if (!m_accel->start()) {
        delete m_accel;
        m_accel = nullptr;
    }

    // Construct our VRPN devices
    m_connection = vrpn_create_server_connection();
    if (m_connection == nullptr) {
      m_statusText += "Could not create VRPN connection\n";
    } else {
      m_buttons = new vrpn_Button_Server("Button0", m_connection, 3);
      m_analogs = new vrpn_Analog_Server("Analog0", m_connection, 3+3+2);
    }

    // Construct our periodic timer that runs 100 times/second
    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(Update()));
    m_timer->start(10);

    // Report our state
    DisplayState();
}

MainWindow::~MainWindow()
{
    delete m_gyro;
    delete m_accel;
    delete m_buttons;
    delete m_analogs;
    if (m_connection) {
      m_connection->removeReference();
      m_connection = nullptr;
    }
    delete ui;
}

void MainWindow::DisplayState()
{
  m_displayText.clear();
  m_displayText += "Button0: 0= " + QString::number((m_button0));
  m_displayText += "; 1= " + QString::number((m_button1));
  m_displayText += "; 2= " + QString::number((m_button2));
  m_displayText += "\n";
  if (m_analogs && m_gyro) {
    m_displayText += "Gyro (Analog0:0-2): = " +
        QString::number((m_analogs->channels()[0])) + "," +
        QString::number((m_analogs->channels()[1])) + "," +
        QString::number((m_analogs->channels()[2])) + "\n";
  }
  if (m_analogs && m_accel) {
    m_displayText += "Accel (Analog0:3-5): = " +
        QString::number((m_analogs->channels()[3+0])) + "," +
        QString::number((m_analogs->channels()[3+1])) + "," +
        QString::number((m_analogs->channels()[3+2])) + "\n";
  }
  m_displayText += "Analog0: 6= " + QString::number((m_analog0));
  m_displayText += "; 7= " + QString::number((m_analog1));
  m_displayText += "\n";
  emit displayText(m_statusText + m_displayText);
}

void MainWindow::Button0Down()
{
  m_button0 = true;
  if (m_buttons) { m_buttons->set_button(0, m_button0); }
  DisplayState();
}

void MainWindow::Button0Up()
{
  m_button0 = false;
  if (m_buttons) { m_buttons->set_button(0, m_button0); }
  DisplayState();
}

void MainWindow::Button1Down()
{
  m_button1 = true;
  if (m_buttons) { m_buttons->set_button(1, m_button1); }
  DisplayState();
}

void MainWindow::Button1Up()
{
  m_button1 = false;
  if (m_buttons) { m_buttons->set_button(1, m_button1); }
  DisplayState();
}

void MainWindow::Button2(bool state)
{
  m_button2 = state;
  if (m_buttons) { m_buttons->set_button(2, m_button2); }
  DisplayState();
}

void MainWindow::Analog0(int percent)
{
  m_analog0 = percent / 100.0;
  if (m_analogs) { m_analogs->channels()[3+3+0] = m_analog0; }
  DisplayState();
}

void MainWindow::Analog1(int percent)
{
  m_analog1 = percent / 100.0;
  if (m_analogs) { m_analogs->channels()[3+3+1] = m_analog1; }
  DisplayState();
}

void MainWindow::HandleGyro()
{
  QGyroscopeReading *reading = m_gyro->reading();
  if (m_analogs && reading) {
    m_analogs->channels()[0] = reading->x();
    m_analogs->channels()[1] = reading->y();
    m_analogs->channels()[2] = reading->z();
    DisplayState();
  }
}

void MainWindow::HandleAccel()
{
  QAccelerometerReading *reading = m_accel->reading();
  if (m_analogs && reading) {
    m_analogs->channels()[3+0] = reading->x();
    m_analogs->channels()[3+1] = reading->y();
    m_analogs->channels()[3+2] = reading->z();
    DisplayState();
  }
}

void MainWindow::Update()
{
  // Send any VRPN reports
  if (m_connection) {
    if (m_analogs) {
      m_analogs->report_changes();
      m_analogs->mainloop();
    }
    if (m_buttons) { m_buttons->mainloop(); }
    m_connection->mainloop();
  }
}
