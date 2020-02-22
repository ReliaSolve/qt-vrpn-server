#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    DisplayState();
}

MainWindow::~MainWindow()
{
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
  emit displayText(m_displayText);
}

void MainWindow::Button0Down()
{
  m_button0 = true;
  DisplayState();
}

void MainWindow::Button0Up()
{
  m_button0 = false;
  DisplayState();
}

void MainWindow::Button1Down()
{
  m_button1 = true;
  DisplayState();
}

void MainWindow::Button1Up()
{
  m_button1 = false;
  DisplayState();
}

void MainWindow::Button2(bool state)
{
  m_button2 = state;
  DisplayState();
}

void MainWindow::Analog0(int percent)
{
  m_analog0 = percent / 100.0;
  DisplayState();
}

void MainWindow::Analog1(int percent)
{
  m_analog1 = percent / 100.0;
  DisplayState();
}

