#pragma once

/**
* version: 1.0
* class name: LbWorldWidget_Abstract
* descrition: 定义用于展示世界的窗口类。该类为抽象类
*/

#include <QWidget>
#include "ui_LbWorldWidget_Abstract.h"
#include "BasicModule/LbWorldData/LbWorldData_Abstract.h"

class LbWorldWidget_Abstract : public QWidget
{
	Q_OBJECT

public:
	LbWorldWidget_Abstract(
		QWidget *parent = nullptr, 
		LbWorldData_Abstract *worldData = nullptr
	);
	~LbWorldWidget_Abstract();

	virtual void setWorldData(LbWorldData_Abstract *worldData) = 0;

protected:
	Ui::LbWorldWidget_AbstractClass ui;
	LbWorldData_Abstract* worldData;
};
