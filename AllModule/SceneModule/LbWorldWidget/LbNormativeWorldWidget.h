#pragma once

/**
* version: 1.0
* class name: LbNormativeWorldWidget
* descrition: 标准展示世界窗口类。
*/

#include <QWidget>
#include "ui_LbNormativeWorldWidget.h"
#include "LbWorldWidget_Abstract.h"

class LbNormativeWorldWidget : public LbWorldWidget_Abstract
{
	Q_OBJECT

public:
	LbNormativeWorldWidget(
		QWidget *parent = nullptr, 
		LbWorldData_Abstract *worldData = nullptr
	);
	~LbNormativeWorldWidget();

	void setWorldData(LbWorldData_Abstract *worldData) override;

private:
	Ui::LbNormativeWorldWidgetClass ui;
};
