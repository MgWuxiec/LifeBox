#include "LbNormativeWorldData.h"

LbNormativeWorldData::LbNormativeWorldData(int width, int height)
{
	value = new int[width * height];
	this->width = width;
    this->height = height;
}

LbNormativeWorldData::~LbNormativeWorldData()
{
	if (value != nullptr) {
		delete value;
		value = nullptr;
	}
}

int LbNormativeWorldData::getCell(int x, int y)
{
    if (x >= width) {
        qDebug() << "LbNormativeData::getCell(int, int): ��ά�����x�����Խ�磡";
    }
    if (y >= height) {
        qDebug() << "LbNormativeData::getCell(int, int): ��ά�����y�����Խ�磡";
    }

    return value[x + y * width];
}

void LbNormativeWorldData::setCell(int x, int y, int cell)
{
    if (x >= width) {
        qDebug() << "LbNormativeData::setCell(int, int, int): ��ά�����x�����Խ�磡";
    }
    if (y >= height) {
        qDebug() << "LbNormativeData::setCell(int, int, int): ��ά�����y�����Խ�磡";
    }

    value[x + y * width] = cell;
}

int LbNormativeWorldData::getWidth()
{
    return width;
}

int LbNormativeWorldData::getHeight()
{
    return height;
}
