#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    QObject* object = new QObject();
}

MainWindow::~MainWindow()
{
    
}
