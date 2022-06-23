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
    setFocusPolicy(Qt::StrongFocus);    //���ô���Ϊ�н���
    setFocus();

    ui.gridLayout->addWidget(&pixelWorld_widgetAnchor.getSliderX(), 1, 0);  //��ӻ�����X��������
    ui.gridLayout->addWidget(&pixelWorld_widgetAnchor.getSliderY(), 0, 1);  //��ӻ�����Y��������
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
    //1. ����painter
    QPainter painter(this);
    QPen pen;
    pen.setColor(DEFAULT_GRIDLINES_COLOR);
    pen.setWidth(DEFAULT_GRIDLINES_WIDTH);
    painter.setPen(pen);

    /**
    * 2. �����ͼ�������յ㡣
    *       Ϊ�˱������֣������ﶨ������������ϵ��
    *           ��������ϵ��ϸ������ϵ
    *       ���Զ�Ӧ�ڴ��ں����磬���Ƿֱ����Լ�����������ϵ��ϸ������ϵ��
    *       ����������㶼�ǻ��ڴ��ڵ���������ϵ
    */
    QPoint pixleWidget_start, pixleWidget_end, temp;

    temp = toCellPoint(pixelWorld_widgetAnchor.point());    //��ʱ������ʼ��
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

    //3. ��ʼ��ͼ
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
