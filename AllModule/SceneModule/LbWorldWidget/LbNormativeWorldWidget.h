#pragma once

/**
* version: 1.1
* class name: LbNormativeWorldWidget
* descrition: 标准展示世界窗口类。
*/

#include <QWidget>
#include <QMouseEvent>
#include <QPainter>
#include <QLayout>
#include <QScrollBar>
#include "ui_LbNormativeWorldWidget.h"
#include "LbWorldWidget_Abstract.h"
#include "SceneModule/LbBoundPoint/LbBoundPoint.h"

const QSize DEFAULT_PIXEL_DIMENSION_OF_CELL(32, 32);
const QPoint DEFAULT_WIDGET_ANCHOR(0, 0);
const QColor DEFAULT_WIDGET_BACKGROUND_COLOR(0, 0, 0);
const QColor DEFAULT_GRIDLINES_COLOR(30, 30, 30);
const QColor DEFAULT_LIVE_CELL_COLOR(186, 135, 243);
const int DEFAULT_GRIDLINES_WIDTH = 1;
const int LAYOUT_LEFT_MARGIN = 512;
const int LAYOUT_RIFHT_MARGIN = 512;
const int LAYOUT_TOP_MARGIN = 256;
const int LAYOUT_BOTTOM_MARGIN = 256;

static bool isSpace = false;
static QPoint pixelWidget_mousePressPoint;
static QPoint pixelWidget_startAnchor;

class LbNormativeWorldWidget : public LbWorldWidget_Abstract
{
	Q_OBJECT

signals:
	void wheelXSignal(QWheelEvent *event);
	void wheelYSignal(QWheelEvent* event);

public:
	LbNormativeWorldWidget(
		QWidget *parent = nullptr, 
		LbWorldData_Abstract *worldData = nullptr
	);
	~LbNormativeWorldWidget();

	void setWorldData(LbWorldData_Abstract *worldData) override;
	void setCellPixelDimension(QSize dimension);

protected:
	void paintEvent(QPaintEvent *event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void wheelEvent(QWheelEvent* event) override;
	void keyPressEvent(QKeyEvent* event) override;
	void keyReleaseEvent(QKeyEvent* event) override;

	void paintCells(QPaintEvent* event);
	void paintGrid(QPaintEvent* event);
	void paintBackground(QPaintEvent* event);

	QPoint toCellPoint(QPoint pixelPoint);
	QPoint toPixelPoint(QPoint cellularPoint);
	QPoint revisePoint(QPoint pixelWorld_point);

protected:
	Ui::LbNormativeWorldWidgetClass ui;

	QSize pixelDimensionOfCell;
	LbBoundPoint pixelWorld_widgetAnchor;
};
