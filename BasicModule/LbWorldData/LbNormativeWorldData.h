#pragma once
#include "LbWorldData_Abstract.h"
#include <QDebug>

/**
* version: 1.0
* class name: LbNormativeWorldData
* descrition: ��׼���������ࡣ���ڴ洢������������ݡ�
*/

class LbNormativeWorldData :
    public LbWorldData_Abstract
{
public:
    LbNormativeWorldData(int width, int height);
    ~LbNormativeWorldData();

    int getCell(int x, int y) override;
    void setCell(int x, int y, int cell) override;
    int getWidth() override;
    int getHeight() override;

protected:
    int *value;

    int width;
    int height;
};
