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

    void initAll();
    void initSceneModule();
    void mousePressEvent(QMouseEvent* event) override;

protected:
    Ui::MainWindowClass ui;

    LbWorldData_Abstract* worldData;
    LbWorldScene_Abstract* scene;
};
