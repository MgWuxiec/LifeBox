#include "LbNormativeWorldWidget.h"
#include <iostream>
using namespace std;

LbNormativeWorldWidget::LbNormativeWorldWidget(
	QWidget *parent,
	LbWorldData_Abstract* worldData
)
	: LbWorldWidget_Abstract(parent, worldData),
      pixelDimensionOfCell(DEFAULT_PIXEL_DIMENSION_OF_CELL)
{
	ui.setupUi(this);

    //设置默认锚点
    ui.widgetAnchorX->setValue(DEFAULT_WIDGET_ANCHOR.x());
    ui.widgetAnchorY->setValue(DEFAULT_WIDGET_ANCHOR.y());

    //初始化X、Y滚动条
    connect(ui.widgetAnchorX, &QScrollBar::valueChanged, [=](){
        update();
        });
    connect(ui.widgetAnchorY, &QScrollBar::valueChanged, [=]() {
        update();
        });

    ui.widgetAnchorX->setMinimum(0);
    ui.widgetAnchorX->setMaximum(worldData->getWidth() * pixelDimensionOfCell.width() + 
                                 LAYOUT_LEFT_MARGIN +
                                 LAYOUT_RIFHT_MARGIN);
    ui.widgetAnchorX->setPageStep(pixelDimensionOfCell.width());
    ui.widgetAnchorX->setSingleStep(pixelDimensionOfCell.width() / 2);

    ui.widgetAnchorY->setMinimum(0);
    ui.widgetAnchorY->setMaximum(worldData->getHeight() * pixelDimensionOfCell.height() +
                                 LAYOUT_TOP_MARGIN +
                                 LAYOUT_BOTTOM_MARGIN);
    ui.widgetAnchorY->setPageStep(pixelDimensionOfCell.height());
    ui.widgetAnchorY->setSingleStep(pixelDimensionOfCell.height() / 2);
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
    start.setX(-ui.widgetAnchorX->value() % pixelDimensionOfCell.width());
    start.setY(-ui.widgetAnchorY->value() % pixelDimensionOfCell.height());
    end.setX(this->width() + pixelDimensionOfCell.width() - this->width() % pixelDimensionOfCell.width());
    end.setY(this->height() + pixelDimensionOfCell.height() - this->height() % pixelDimensionOfCell.height());

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
