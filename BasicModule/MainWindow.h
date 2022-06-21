#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"

#include <QObject>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindowClass ui;
};