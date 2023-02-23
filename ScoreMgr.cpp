#include "ScoreMgr.h"
#include "Define.h"

#include <DxLib.h>

ScoreMgr::ScoreMgr()
{
	this->init();
}

void ScoreMgr::init()
{
	_score = 0;
	_time = 0;
	_preCount = GetNowCount();
	_stopFlag = false;
}

bool ScoreMgr::update()
{
	int nowCount = GetNowCount();

	if (!_stopFlag)
	{
		_time += (nowCount - _preCount);
	}

	_preCount = nowCount;

	return true;
}

void ScoreMgr::IncScore(int n)
{
	_score += n;
}

void ScoreMgr::draw() const
{
	DrawFormatString(Define::GAME_SCORE_X, Define::GAME_SCORE_Y, GetColor(255, 255, 255), "score : %d", _score);

	int t = _time / 1000;
	DrawFormatString(Define::GAME_TIME_X, Define::GAME_TIME_Y, GetColor(255, 255, 255), " time : %02d'%02d", t / 60, t % 60);
}

int ScoreMgr::getTime()
{
	return (GetNowCount() - _time) / 1000;
}