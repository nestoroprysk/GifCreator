#pragma once

#include <string>

class INameable
{
public:
	virtual auto getName() const -> const std::string& = 0;
	virtual ~INameable() {}
};
