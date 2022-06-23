#include "LbNormativeWorldWidget.h"
#include <iostream>
using namespace std;

LbNormativeWorldWidget::LbNormativeWorldWidget(
	QWidget *parent,
	LbWorldData_Abstract* worldData
)
	: LbWorldWidget_Abstract(parent, worldData),
      pixelDimensionOfCell(DEFAULT_PIXEL_DIMENSION_OF_CELL),
      pixelWorld_widgetAnchor(
          this,
          QPoint(-LAYOUT_LEFT_MARGIN, -LAYOUT_TOP_MARGIN), 
          QPoint(worldData->getWidth() * pixelDimensionOfCell.width() + LAYOUT_RIFHT_MARGIN, 
                 worldData->getHeight()* pixelDimensionOfCell.height() + LAYOUT_BOTTOM_MARGIN)
      )
{
	ui.setupUi(this);
    setFocusPolicy(Qt::StrongFocus);    //设置窗口为有焦点
    setFocus();

    ui.gridLayout->addWidget(&pixelWorld_widgetAnchor.getSliderX(), 1, 0);  //添加滑动条X到布局中
    ui.gridLayout->addWidget(&pixelWorld_widgetAnchor.getSliderY(), 0, 1);  //添加滑动条Y到布局中
}

LbNormativeWorldWidget::~LbNormativeWorldWidget()
{
}

void LbNormativeWorldWidget::setWorldData(LbWorldData_Abstract* worldData)
{
	this->worldData = worldData;
}

void LbNormativeWorldWidget::setCellPixelDimension(QSize dimension)
{
    pixelDimensionOfCell = dimension;
}

void LbNormativeWorldWidget::paintEvent(QPaintEvent* event)
{
	if (worldData == nullptr) {
		qDebug() << "LbNormativeScene::paintEvent(QPaintEvent*)：变量worldData是空指针！请检查是否正确链接LbWorldData_Abstract实例对象。";
		return;
	}

	paintCells(event);
    paintGrid(event);
}

void LbNormativeWorldWidget::mousePressEvent(QMouseEvent* event)
{

}

void LbNormativeWorldWidget::mouseReleaseEvent(QMouseEvent* event)
{

}

void LbNormativeWorldWidget::mouseMoveEvent(QMouseEvent* event)
{
    if (isSpace) {
        setCursor(Qt::ClosedHandCursor);
    }
}

void LbNormativeWorldWidget::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Space) {
        setCursor(Qt::OpenHandCursor);
        isSpace = true;
    }
}

void LbNormativeWorldWidget::keyReleaseEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Space) {
        static int i = 0;
        qDebug() << i++;
        setCursor(Qt::ArrowCursor);
        isSpace = false;
    }
}

void LbNormativeWorldWidget::paintCells(QPaintEvent* event)
{

}

void LbNormativeWorldWidget::paintGrid(QPaintEvent* event)
{
    //1. 定义painter
    QPainter painter(this);
    QPen pen;
    pen.setColor(DEFAULT_GRIDLINES_COLOR);
    pen.setWidth(DEFAULT_GRIDLINES_WIDTH);
    painter.setPen(pen);

    /**
    * 2. 定义绘图的起点和终点。
    *       为了便于区分，在这里定义了两种坐标系：
    *           像素坐标系、细胞坐标系
    *       所以对应于窗口和世界，它们分别都有自己的像素坐标系和细胞坐标系。
    *       这里的两个点都是基于窗口的像素坐标系
    */
    QPoint pixleWidget_start, pixleWidget_end, temp;

    temp = toCellPoint(pixelWorld_widgetAnchor.point());    //临时变量初始化
    if (temp.x() < 0) {
        temp.setX(0);
    }
    else if (temp.x() > worldData->getWidth()) {
        temp.setX(worldData->getWidth());
    }
    if (temp.y() < 0) {
        temp.setY(0);
    }
    else if (temp.y() > worldData->getHeight()) {
        temp.setY(worldData->getHeight());
    }
    temp = toPixelPoint(temp);
    temp = temp - pixelWorld_widgetAnchor.point();
    pixleWidget_start = temp;

    temp = toCellPoint(pixelWorld_widgetAnchor.point() + QPoint(this->width(), this->height())) + 
           QPoint(1, 1);
    if (temp.x() < 0) {
        temp.setX(0);
    }
    else if (temp.x() > worldData->getWidth()) {
        temp.setX(worldData->getWidth());
    }
    if (temp.y() < 0) {
        temp.setY(0);
    }
    else if (temp.y() > worldData->getHeight()) {
        temp.setY(worldData->getHeight());
    }
    temp = toPixelPoint(temp);
    temp = temp - pixelWorld_widgetAnchor.point();
    pixleWidget_end = temp;

    //3. 开始绘图
    for (int i = pixleWidget_start.x(); i <= pixleWidget_end.x(); i += pixelDimensionOfCell.width()) {
        painter.drawLine(i, pixleWidget_start.y(), i, pixleWidget_end.y());
    }
    for (int i = pixleWidget_start.y(); i <= pixleWidget_end.y(); i += pixelDimensionOfCell.height()) {
        painter.drawLine(pixleWidget_start.x(), i, pixleWidget_end.x(), i);
    }
}

void LbNormativeWorldWidget::paintBackground(QPaintEvent* event)
{

}

QPoint LbNormativeWorldWidget::toCellPoint(QPoint pixelPoint)
{
    return QPoint((int)pixelPoint.x() / pixelDimensionOfCell.width(),
                  (int)pixelPoint.y() / pixelDimensionOfCell.height());
}

QPoint LbNormativeWorldWidget::toPixelPoint(QPoint cellularPoint)
{
    return QPoint((int)cellularPoint.x() * pixelDimensionOfCell.width(),
                  (int)cellularPoint.y() * pixelDimensionOfCell.height());
}
