#include "LbBoundPoint.h"

LbBoundPoint::LbBoundPoint(QWidget* parent, QPoint pos1, QPoint pos2)
	: sliderX(parent), sliderY(parent)
{
	setRange(pos1, pos2);

	connect(&sliderX, &QAbstractSlider::valueChanged, [=]() {
		parent->update();
		});
	connect(&sliderY, &QAbstractSlider::valueChanged, [=]() {
		parent->update();
		});

	sliderX.setOrientation(Qt::Horizontal);
	sliderY.setOrientation(Qt::Vertical);

	//³õÊ¼»¯Öµ
	sliderX.setValue(-xMin);
	sliderY.setValue(-yMin);
}

int LbBoundPoint::x()
{
	return sliderX.value() + xMin;
}

int LbBoundPoint::y()
{
	return sliderY.value() + yMin;
}

QPoint LbBoundPoint::point()
{
	return QPoint(x(), y());
}

void LbBoundPoint::setX(int value)
{
	sliderX.setValue(value - xMin);
}

void LbBoundPoint::setY(int value)
{
	sliderY.setValue(value - yMin);
}

QScrollBar& LbBoundPoint::getSliderX()
{
	return sliderX;
}

QScrollBar& LbBoundPoint::getSliderY()
{
	return sliderY;
}

void LbBoundPoint::setRange(QPoint pos1, QPoint pos2)
{
	if (pos1.x() > pos2.x()) {
		xMax = pos1.x();
		xMin = pos2.x();
	}
	else {
		xMax = pos2.x();
		xMin = pos1.x();
	}
	if (pos1.y() > pos2.y()) {
		yMax = pos1.y();
		yMin = pos2.y();
	}
	else {
		yMax = pos2.y();
		yMin = pos1.y();
	}

	sliderX.setMinimum(0);
	sliderX.setMaximum(xMax - xMin);
	qDebug() << xMax - xMin;
	sliderY.setMinimum(0);
	sliderY.setMaximum(yMax - yMin);
}
