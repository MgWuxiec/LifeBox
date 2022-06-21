#include "LbNormativeWorldScene.h"

LbNormativeWorldScene::LbNormativeWorldScene(LbWorldWidget_Abstract* widget):
	LbWorldScene_Abstract(widget)
{
}

void LbNormativeWorldScene::updateScene()
{
	widget->update();
}

void LbNormativeWorldScene::setWorldData(LbWorldData_Abstract* worldData)
{
	widget->setWorldData(worldData);
}
