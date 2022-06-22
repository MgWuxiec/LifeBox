#pragma once

/**
* version: 1.0
* class name: LbBoundPoint
* descrition: 绑定了两个滚动条的点
*/

#include <QPoint>
#include <QScrollBar>
#include <QDebug>

class LbBoundPoint: public QObject
{
	Q_OBJECT

public:
	LbBoundPoint(QWidget* parent, QPoint pos1, QPoint pos2);
	int x();
	int y();
	void setX(int value);
	void setY(int value);
	QScrollBar& getSliderX();
	QScrollBar& getSliderY();
	void setRange(QPoint pos1, QPoint pos2);

protected:
	int xMin;
	int xMax;
	int yMin;
	int yMax;

	QScrollBar sliderX;
	QScrollBar sliderY;
};
