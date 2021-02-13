#pragma once

#include <string>

class IScene
{
public:
	virtual ~IScene() = default;

public:
	virtual void Draw() = 0;

public:
	virtual const std::string& GetName() const = 0;
};