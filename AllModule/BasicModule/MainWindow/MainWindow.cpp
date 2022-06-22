#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    LbWorldData_Abstract* worldData = new LbNormativeWorldData(16, 16);
    LbWorldWidget_Abstract* widget = new LbNormativeWorldWidget(this, worldData);
    LbWorldScene_Abstract* scene = new LbNormativeWorldScene(widget);
    setCentralWidget(widget);
}

MainWindow::~MainWindow()
{
    
}
