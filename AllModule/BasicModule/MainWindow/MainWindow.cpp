#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    LbWorldData_Abstract* worldData = new LbNormativeWorldData(256, 256);
    LbWorldWidget_Abstract* widget = new LbNormativeWorldWidget(this, worldData);
    LbWorldScene_Abstract* scene = new LbNormativeWorldScene(widget);
    setCentralWidget(widget);
}

MainWindow::~MainWindow()
{
    
}
