#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include <QObject>
#include "BasicModule/LbWorldData/LbNormativeWorldData.h"
#include "SceneModule/LbWorldScene/LbNormativeWorldScene.h"
#include "SceneModule/LbWorldWidget/LbNormativeWorldWidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindowClass ui;
};
