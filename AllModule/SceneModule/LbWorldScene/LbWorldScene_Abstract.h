#pragma once

/**
* version: 1.0
* class name: LbWorldScene_Abstract
* descrition: 定义用于展示世界的舞台类。该类更像是接口。
*/

#include"SceneModule/LbWorldWidget/LbWorldWidget_Abstract.h"

class LbWorldScene_Abstract
{
public:
	LbWorldScene_Abstract(LbWorldWidget_Abstract *widget);
	virtual void updateScene() = 0;
	virtual void setWorldData(LbWorldData_Abstract* worldData) = 0;

protected:
	LbWorldWidget_Abstract* widget;
};

