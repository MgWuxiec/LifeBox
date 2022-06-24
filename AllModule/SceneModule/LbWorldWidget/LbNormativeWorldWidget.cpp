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
    connect(this, &LbNormativeWorldWidget::wheelXSignal, &pixelWorld_widgetAnchor.getSliderX(), &QScrollBar::event);
    connect(this, &LbNormativeWorldWidget::wheelYSignal, &pixelWorld_widgetAnchor.getSliderY(), &QScrollBar::event);
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
    pixelWidget_mousePressPoint.setX(event->x());
    pixelWidget_mousePressPoint.setY(event->y());
    pixelWidget_startAnchor = pixelWorld_widgetAnchor.point();

    switch (event->button()) {
    case Qt::LeftButton: {
        if (isSpace == false) {
            QPoint temp = pixelWidget_mousePressPoint + pixelWorld_widgetAnchor.point();
            temp = toCellPoint(temp);

            if (temp.x() >= 0 && temp.x() <= worldData->getWidth() &&
                temp.y() >= 0 && temp.y() <= worldData->getHeight()) {
                worldData->setCell(temp.x(), temp.y(), 1);
            }
        }
        update();
        break;
    }

    case Qt::RightButton: {
        if (isSpace == false) {
            QPoint temp = pixelWidget_mousePressPoint + pixelWorld_widgetAnchor.point();
            temp = toCellPoint(temp);

            if (temp.x() >= 0 && temp.x() <= worldData->getWidth() &&
                temp.y() >= 0 && temp.y() <= worldData->getHeight()) {
                worldData->setCell(temp.x(), temp.y(), 0);
            }
        }
        update();
        break;
    }

    default: {
        break;
    }
    }
}

void LbNormativeWorldWidget::mouseReleaseEvent(QMouseEvent* event)
{
    if (isSpace == true) {
        setCursor(Qt::OpenHandCursor);
    }
}

void LbNormativeWorldWidget::mouseMoveEvent(QMouseEvent* event)
{
    switch (event->buttons()) {
    case Qt::LeftButton: {
        //鼠标拖动操作
        if (isSpace == true) {
            setCursor(Qt::ClosedHandCursor);
            int deltaX = event->x() - pixelWidget_mousePressPoint.x();
            int deltaY = event->y() - pixelWidget_mousePressPoint.y();
            pixelWorld_widgetAnchor.setX(pixelWidget_startAnchor.x() - deltaX);
            pixelWorld_widgetAnchor.setY(pixelWidget_startAnchor.y() - deltaY);
        }

        //鼠标绘制操作
        else if (isSpace == false){
            QPoint temp = QPoint(event->x(), event->y()) + pixelWorld_widgetAnchor.point();
            temp = toCellPoint(temp);

            if (temp.x() >= 0 && temp.x() <= worldData->getWidth() &&
                temp.y() >= 0 && temp.y() <= worldData->getHeight()) {
                worldData->setCell(temp.x(), temp.y(), 1);
            }
            update();
        }
        break;
    }
                       
    case Qt::RightButton : {
        if (isSpace == false) {
            QPoint temp = QPoint(event->x(), event->y()) + pixelWorld_widgetAnchor.point();
            temp = toCellPoint(temp);

            if (temp.x() >= 0 && temp.x() <= worldData->getWidth() &&
                temp.y() >= 0 && temp.y() <= worldData->getHeight()) {
                worldData->setCell(temp.x(), temp.y(), 0);
            }
            update();
        }
        break;
    }

    default: {
        qDebug() << "无效操作";
        break;
    }
    }
}

void LbNormativeWorldWidget::wheelEvent(QWheelEvent* event)
{
    //发送信号
    switch (event->modifiers()) {
    case Qt::ShiftModifier: {
        emit wheelXSignal(event);
        break;
    }

    case Qt::NoModifier: {
        emit wheelYSignal(event);
        break;
    }

    case Qt::AltModifier: {


        break;
    }

    default: {
        break;
    }
    }
}

void LbNormativeWorldWidget::keyPressEvent(QKeyEvent* event)
{
    switch (event->key()) {
    case Qt::Key_Space: {
        if (!event->isAutoRepeat()) {
            setCursor(Qt::OpenHandCursor);
            isSpace = true;
        }
        break;
    }
    default: {
        break;
    }
    }
}

void LbNormativeWorldWidget::keyReleaseEvent(QKeyEvent* event)
{
    switch (event->key()) {
    case Qt::Key_Space: {
        //static int i = 0;
        //qDebug() << i++;
        if (!event->isAutoRepeat()) {
            setCursor(Qt::ArrowCursor);
            isSpace = false;
        }
        break;
    }
    default: {
        break;
    }
    }
}

void LbNormativeWorldWidget::paintCells(QPaintEvent* event)
{
    //1. 定义painter
    QPainter painter(this);
    QPen pen;
    painter.setBrush(DEFAULT_LIVE_CELL_COLOR);
    painter.setPen(pen);

    //2. 求出绘图起点和终点
    QPoint pixelWidget_start = revisePoint(pixelWorld_widgetAnchor.point()) -
                                           pixelWorld_widgetAnchor.point(),

        pixelWidget_end = revisePoint(pixelWorld_widgetAnchor.point() + QPoint(this->width(), this->height())) -
                                      pixelWorld_widgetAnchor.point();

    /**
    * ======================================
    * 3. 绘制细胞
    *       这里是临时代码、应该使用迭代器提高效率！
    */
    for (int i = 0; i < worldData->getWidth(); i++) {
        for (int e = 0; e < worldData->getHeight(); e++) {
            if (worldData->getCell(i, e) == 1) {
                QPoint start = toPixelPoint(QPoint(i, e)) - pixelWorld_widgetAnchor.point();

                if (start.x() >= pixelWidget_start.x() && start.y() >= pixelWidget_start.y() &&
                    start.x() <= pixelWidget_end.x() && start.y() <= pixelWidget_end.y()) {
                    painter.drawRect(
                        start.x(),
                        start.y(),
                        pixelDimensionOfCell.width(),
                        pixelDimensionOfCell.height()
                    );
                }
            }
        }
    }
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
    * 
    *       要理解如何求出绘图的起点和终点，首先要理解revisePoint()函数的作用是什么。
    */
    QPoint pixelWidget_start = revisePoint(pixelWorld_widgetAnchor.point()) - 
                                           pixelWorld_widgetAnchor.point(),

           pixelWidget_end = revisePoint(pixelWorld_widgetAnchor.point() + QPoint(this->width(), this->height())) - 
                             pixelWorld_widgetAnchor.point() +
                             QPoint(pixelDimensionOfCell.width(), pixelDimensionOfCell.height());

    //3. 开始绘图
    for (int i = pixelWidget_start.x(); i <= pixelWidget_end.x(); i += pixelDimensionOfCell.width()) {
        painter.drawLine(i, pixelWidget_start.y(), i, pixelWidget_end.y());
    }
    for (int i = pixelWidget_start.y(); i <= pixelWidget_end.y(); i += pixelDimensionOfCell.height()) {
        painter.drawLine(pixelWidget_start.x(), i, pixelWidget_end.x(), i);
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

QPoint LbNormativeWorldWidget::revisePoint(QPoint pixelWorld_point)
{
    QPoint temp = toCellPoint(pixelWorld_point);

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
    return temp;
}
