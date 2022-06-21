#pragma once

/**
* version: 1.0
* class name: LbNormativeWorldScene
* descrition: 展示世界的舞台类，里面放了个Widget。
*/

#include "LbWorldScene_Abstract.h"

class LbNormativeWorldScene :
    public LbWorldScene_Abstract
{
public:
    LbNormativeWorldScene(LbWorldWidget_Abstract* widget);

	void updateScene() override;
	void setWorldData(LbWorldData_Abstract* worldData);
};
