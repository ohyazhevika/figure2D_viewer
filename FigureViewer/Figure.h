#ifndef FIGURE_H
#define FIGURE_H

class Figure
{
protected:
	int size;
	int offsetX, offsetY;
private:
	bool isDragging;
	int previousX, previousY;
public:
	Figure(int size, int offsetX, int offsetY) : size(size), offsetX(offsetX), offsetY(offsetY), isDragging(false), previousX(0), previousY(0)
	{
	}
	void Clear(HDC dc)
	{
		RECT r;
		GetClientRect(WindowFromDC(dc), &r);
		Rectangle(dc, 0, 0, r.right, r.bottom);
		MoveToEx(dc, 0, 0, nullptr);
	}
	virtual void Draw(HDC dc) = 0;
	virtual bool InnerPoint(int X, int Y) = 0;
	void MoveTo(int X, int Y)
	{
		offsetX=X;
		offsetY=Y;
	}
	void Move(int X, int Y)
	{
		offsetX += X;
		offsetY += Y;
	}
	void StartDragging(int X, int Y)
	{
		previousX = X - offsetX;
		previousY = Y - offsetY;
		isDragging = true;
	}
	void Drag(int X, int Y)
	{//сделать так, чтобы при хватании фигуры и перетаскивании, учитывалось √ƒ≈ мы поставили курсор внутри самой фигуры
			MoveTo(X-previousX, Y-previousY);
	}
	void StopDragging()
	{
		previousX = 0;
		previousY = 0;
		isDragging = false;
	}
	bool IsDragging()
	{
		return isDragging;
	}
	void PlusSize()
	{
		size = size + 1;
	}
	void MinusSize()
	{	if (size>2)
		size = size - 1;
	}
	void SwitchTo(int _size, int _offsetX, int _offsetY)
	{
		size = _size;
		offsetX = _offsetX;
		offsetY = _offsetY;
	}
	int GetSize()
	{
		return size;
	}
	int GetOffsetX()
	{
		return offsetX;
	}
	int GetOffsetY()
	{
		return offsetY;
	}
};

#endif FIGURE_H
