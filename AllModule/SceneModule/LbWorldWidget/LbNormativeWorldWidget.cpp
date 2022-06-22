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

    //����Ĭ��ê��
    ui.widgetAnchorX->setValue(DEFAULT_WIDGET_ANCHOR.x());
    ui.widgetAnchorY->setValue(DEFAULT_WIDGET_ANCHOR.y());

    //��ʼ��X��Y������
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
		qDebug() << "LbNormativeScene::paintEvent(QPaintEvent*)������worldData�ǿ�ָ�룡�����Ƿ���ȷ����LbWorldData_Abstractʵ������";
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
    //1. ����painter
    QPainter painter(this);
    QPen pen;
    pen.setColor(DEFAULT_GRIDLINES_COLOR);
    pen.setWidth(DEFAULT_GRIDLINES_WIDTH);
    painter.setPen(pen);

    //2. �����ͼ�������յ㣬��sceneΪ������ϵ
    QPoint start, end;
    start.setX(-ui.widgetAnchorX->value() % pixelDimensionOfCell.width());
    start.setY(-ui.widgetAnchorY->value() % pixelDimensionOfCell.height());
    end.setX(this->width() + pixelDimensionOfCell.width() - this->width() % pixelDimensionOfCell.width());
    end.setY(this->height() + pixelDimensionOfCell.height() - this->height() % pixelDimensionOfCell.height());

    //3. ��ʼ��ͼ
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
