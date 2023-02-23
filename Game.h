#pragma once

class AbstractGame
{
public:
	AbstractGame() {};
	virtual ~AbstractGame() = default;
	virtual void initialize() = 0;
	virtual bool update() = 0;
	virtual void finalize() = 0;
	virtual void draw() const = 0;
};