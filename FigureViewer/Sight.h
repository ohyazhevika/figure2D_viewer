#ifndef SIGHT_H
#define SIGHT_H

#include "Figure.h"

class Sight : public Figure
{
public:
	Sight(int size=30, int offsetX=120, int offsetY=140) : Figure(size, offsetX, offsetY)
	{
	}
	void Draw(HDC dc)
	{
		Ellipse( dc, offsetX - size, offsetY-size, offsetX+size, offsetY+size);
		MoveToEx(dc, offsetX-size, offsetY,      NULL);
		LineTo(  dc, offsetX+size, offsetY);
		MoveToEx(dc, offsetX,      offsetY-size, NULL);
		LineTo(  dc, offsetX,      offsetY+size);
	}
	bool InnerPoint(int X, int Y)
	{
		return (X-offsetX)*(X-offsetX)+(Y-offsetY)*(Y-offsetY)<=size*size;
	}
};

class Square : public Figure
{
public: 
	Square(int size = 30, int offsetX = 120, int offsetY = 140) : Figure(size, offsetX, offsetY) {};
	void Draw(HDC dc)
	{
		MoveToEx(dc, offsetX - size, offsetY - size, NULL);
		LineTo(dc, offsetX - size, offsetY + size);
		LineTo(dc, offsetX + size, offsetY + size);
		LineTo(dc, offsetX + size, offsetY - size);
		LineTo(dc, offsetX - size, offsetY - size);
		LineTo(dc, offsetX + size, offsetY + size);
		MoveToEx(dc, offsetX + size, offsetY - size, NULL);
		LineTo(dc, offsetX - size, offsetY + size);
	}
	bool InnerPoint(int X, int Y)
	{
		return true;
	}
	
};
#endif SIGHT_H
