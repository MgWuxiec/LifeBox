#pragma once

/**
* version: 1.0
* class name: LbWorldWidget_Abstract
* descrition: ��������չʾ����Ĵ����ࡣ����Ϊ������
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
