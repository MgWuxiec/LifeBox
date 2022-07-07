#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    initAll();
}

MainWindow::~MainWindow()
{
    
}

void MainWindow::initAll()
{
    worldData = new LbNormativeWorldData(32, 32);
    initSceneModule();
}

void MainWindow::initSceneModule()
{
    LbWorldWidget_Abstract* widget = new LbNormativeWorldWidget(this, worldData);
    scene = new LbNormativeWorldScene(widget);
    setCentralWidget(widget);
}

void MainWindow::mousePressEvent(QMouseEvent* event)
{

}
