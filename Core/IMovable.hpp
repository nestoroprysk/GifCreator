#pragma once

#include <string>

class IMovable
{
public:
	struct moveUp;
	struct moveDown;
	struct moveLeft;
	struct moveRight;

public:
	struct moveUp{
		moveDown mirror() const { return moveDown(); }
		auto get() const { return &IMovable::_moveUp; }
	};
	struct moveDown{
		moveUp mirror() const { return moveUp(); }
		auto get() const { return &IMovable::_moveDown; }
	};
	struct moveLeft{
		moveRight mirror() const { return moveRight(); }
		auto get() const { return &IMovable::_moveLeft; }
	};
	struct moveRight{
		moveLeft mirror() const { return moveLeft(); }
		auto get() const { return &IMovable::_moveRight; }
	};

protected:
	virtual void _moveUp() = 0;
	virtual void _moveDown() = 0;
	virtual void _moveLeft() = 0;
	virtual void _moveRight() = 0;
	virtual ~IMovable() {}
};
