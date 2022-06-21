#include "LbNormativeWorldWidget.h"

LbNormativeWorldWidget::LbNormativeWorldWidget(
	QWidget *parent,
	LbWorldData_Abstract* worldData
)
	: LbWorldWidget_Abstract(parent, worldData)
{
	ui.setupUi(this);
}

LbNormativeWorldWidget::~LbNormativeWorldWidget()
{}

void LbNormativeWorldWidget::setWorldData(LbWorldData_Abstract* worldData)
{
	this->worldData = worldData;
}
