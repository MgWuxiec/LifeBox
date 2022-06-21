#pragma once

/**
* version: 1.0
* class name: LbWorldData_Abstract
* descrition: 抽象世界数据类。定义数据功能。
*/

class LbWorldData_Abstract
{
public:
	virtual ~LbWorldData_Abstract();

	virtual int getCell(int x, int y) = 0;
	virtual void setCell(int x, int y, int cell) = 0;
	virtual int getWidth() = 0;
	virtual int getHeight() = 0;
};
