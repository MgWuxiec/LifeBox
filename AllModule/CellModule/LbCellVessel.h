#pragma once
#include <QVector>

class LbCellVessel
{
public:
	static void addCell();
	static void creator();

protected:
	static QVector<int> vessel;

private:
	LbCellVessel();
};

