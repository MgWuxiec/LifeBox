#include "LbWorldWidget_Abstract.h"


LbWorldWidget_Abstract::LbWorldWidget_Abstract(
	QWidget *parent, 
	LbWorldData_Abstract *worldData
)
	: QWidget(parent), worldData(worldData)
{
	ui.setupUi(this);
}

LbWorldWidget_Abstract::~LbWorldWidget_Abstract()
{}
