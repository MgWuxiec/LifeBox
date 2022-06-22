#include "LbNormativeWorldWidget.h"
#include <iostream>
using namespace std;

LbNormativeWorldWidget::LbNormativeWorldWidget(
	QWidget *parent,
	LbWorldData_Abstract* worldData
)
	: LbWorldWidget_Abstract(parent, worldData),
      pixelDimensionOfCell(DEFAULT_PIXEL_DIMENSION_OF_CELL),
      anchorWidget(
          this,
          QPoint(-LAYOUT_LEFT_MARGIN, -LAYOUT_TOP_MARGIN), 
          QPoint(worldData->getWidth() * pixelDimensionOfCell.width() + LAYOUT_RIFHT_MARGIN, 
                 worldData->getHeight()* pixelDimensionOfCell.height() + LAYOUT_BOTTOM_MARGIN)
      )
{
	ui.setupUi(this);

    ui.gridLayout->addWidget(&anchorWidget.getSliderX(), 1, 0);
    ui.gridLayout->addWidget(&anchorWidget.getSliderY(), 0, 1);
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

    //2. 定义绘图的起点和终点，以scene为基坐标系
    QPoint start, end;
    if (anchorWidget.x() >= 0) {
        start.setX(-anchorWidget.x() % pixelDimensionOfCell.width());
    }
    else {
        start.setX(-anchorWidget.x());
    }
    if (anchorWidget.y() >= 0) {
        start.setY(-anchorWidget.y() % pixelDimensionOfCell.height());
    }
    else {
        start.setY(-anchorWidget.y());
    }

    if (start.x() + pixelDimensionOfCell.width() * worldData->getWidth() >= this->width()) {
        end.setX(this->width() + pixelDimensionOfCell.width() - this->width() % pixelDimensionOfCell.width());
    }
    else {
        end.setX(this->width() + start.x() + pixelDimensionOfCell.width() * worldData->getWidth());
    }
    if (start.y() + pixelDimensionOfCell.height() * worldData->getHeight() >= this->height()) {
        end.setY(this->height() + pixelDimensionOfCell.height() - this->height() % pixelDimensionOfCell.height());
    }
    else {
        end.setY(this->height() + start.y() + pixelDimensionOfCell.height() * worldData->getHeight());
    }

    //3. 开始绘图
    for (int i = start.x(); i < end.x(); i += pixelDimensionOfCell.width()) {
        painter.drawLine(i, start.y(), i, end.y());
    }
    for (int i = start.y(); i < end.y(); i += pixelDimensionOfCell.height()) {
        painter.drawLine(start.x(), i, end.x(), i);
    }
}

void LbNormativeWorldWidget::paintBackground(QPaintEvent* event)
{

}
