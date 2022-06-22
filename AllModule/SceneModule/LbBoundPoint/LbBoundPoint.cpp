#include "LbBoundPoint.h"

LbBoundPoint::LbBoundPoint(QWidget* parent, QPoint pos1, QPoint pos2)
	: sliderX(parent), sliderY(parent)
{
	setRange(pos1, pos2);

/*	connect(&sliderX, &QAbstractSlider::valueChanged, [=]() {
		parent->update();
		});
	connect(&sliderY, &QAbstractSlider::valueChanged, [=]() {
		parent->update();
		})*/;
}

int LbBoundPoint::x()
{
	return sliderX.value() + xMin;
}

int LbBoundPoint::y()
{
	return sliderY.value() + yMin;
}

void LbBoundPoint::setX(int value)
{
	sliderX.setValue(value - xMin);
}

void LbBoundPoint::setY(int value)
{
	sliderY.setValue(value - yMin);
}

QAbstractSlider& LbBoundPoint::getSliderX()
{
	return sliderX;
}

QAbstractSlider& LbBoundPoint::getSliderY()
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
		xMax = pos1.y();
		xMin = pos2.y();
	}
	else {
		xMax = pos2.y();
		xMin = pos1.y();
	}

	sliderX.setMinimum(0);
	sliderX.setMaximum(xMax - xMin);
	sliderY.setMinimum(0);
	sliderY.setMaximum(yMax - xMin);
}
