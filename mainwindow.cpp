#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Find out what types of sensors we have available
    QList<QByteArray> sts = QSensor::sensorTypes();
    m_statusText += "Sensor types:\n";
    for (auto t : sts) {
      m_statusText += "  " + t + "\n";
    }

    // Construct our VRPN devices
    m_connection = vrpn_create_server_connection();
    if (m_connection == nullptr) {
      m_statusText += "Could not create VRPN connection\n";
    } else {
      m_buttons = new vrpn_Button_Server("Button0", m_connection, 3);
      m_analogs = new vrpn_Analog_Server("Analog0", m_connection, 2);
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
    delete m_buttons;
    delete m_analogs;
    delete m_connection;
    delete ui;
}

void MainWindow::DisplayState()
{
  m_displayText.clear();
  m_displayText += "Buttons: 0= " + QString::number((m_button0));
  m_displayText += "; 1= " + QString::number((m_button1));
  m_displayText += "; 2= " + QString::number((m_button2));
  m_displayText += "\n";
  m_displayText += "Analogs: 0= " + QString::number((m_analog0));
  m_displayText += "; 1= " + QString::number((m_analog1));
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
  if (m_analogs) { m_analogs->channels()[0] = m_analog0; }
  DisplayState();
}

void MainWindow::Analog1(int percent)
{
  m_analog1 = percent / 100.0;
  if (m_analogs) { m_analogs->channels()[1] = m_analog1; }
  DisplayState();
}

void MainWindow::Update()
{
  if (m_connection) {

    if (m_analogs) {
      m_analogs->report_changes();
      m_analogs->mainloop();
    }
    if (m_buttons) { m_buttons->mainloop(); }
    m_connection->mainloop();
  }
}
