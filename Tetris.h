#pragma once

#include "Game.h"
#include "IIncScoreListener.h"

#include <vector>
#include <memory>

enum eMinoType {
	TYPE_I,
	TYPE_O,
	TYPE_S,
	TYPE_Z,
	TYPE_J,
	TYPE_L,
	TYPE_T,
	MinoNum
};

enum eMinoAngle {
	Angle_0,
	Angle_90,
	Angle_180,
	Angle_270,
	MinoAngleNum
};

class Obj
{
public:
	Obj(int color, int x, int y) : _color(color), _x(x), _y(y) {};
	~Obj() = default;
	int _color;
	int _x;
	int _y;
};

class Tetris final : public AbstractGame
{
public:
	Tetris(std::shared_ptr<IIncScoreListener> implScore);
	~Tetris() = default;

	void initialize() override;
	void finalize() override;
	bool update() override;
	void draw() const override;

private:
	unsigned int _cnt;
	std::shared_ptr<IIncScoreListener> _implScore;

	// Now Mino
	int _nowType;
	int _nowAngle;
	std::vector<std::shared_ptr<Obj>> _nowMino;
	std::vector<std::pair<int, int>> _minoAngleInfo;

	// Next Mino
	int _nextType;
	std::vector<std::shared_ptr<Obj>> _nextMino;

	// Keep Mino
	bool _changeFlag;
	int _keepType;
	std::vector<std::shared_ptr<Obj>> _keepMino;

	// ”Õ–Ê
	std::vector<std::vector<std::shared_ptr<Obj>>> _field;

	bool IsHit(int, int);

	void setNextMino();

	void eraceLine();
};