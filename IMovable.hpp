#pragma once

class IMovable
{
public:
	virtual void gotoCenter() = 0;
	virtual void moveUp() = 0;
	virtual void moveDown() = 0;
	virtual void moveLeft() = 0;
	virtual void moveRight() = 0;
	virtual ~IMovable() {}
};
