#include "GameScene.h"
#include "Keyboard.h"
#include "Define.h"
#include "eScene.h"
#include "Tetris.h"

#include <DxLib.h>

using namespace std;

GameScene::GameScene(IOnSceneChangedListener* impl, const Parameter& parameter) : AbstractScene(impl, parameter)
{
	_nowSelect = 0;
	_pauseFlag = false;
	_implScore = make_shared<ScoreMgr>();
	_implGame = unique_ptr<Tetris>(new Tetris(_implScore));
}

void GameScene::initialize()
{
	_nowSelect = 0;
	_implGame->initialize();
}

bool GameScene::update()
{
	_implScore->update();

	if (!_pauseFlag)
	{
		if (!_implGame->update()) {
			Parameter param;
			const bool stackClear = true;

			param.set("ParameterTagResultScore", _implScore->getFilalScore());
			param.set("ParameterTagTime", _implScore->getTime());

			_implSceneChanged->onSceneChanged(eScene::Result, param, stackClear);
		}
	}

	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_ESCAPE) == 1) {
		_pauseFlag = !_pauseFlag;
		if (_pauseFlag) _implScore->stopTime();
		else _implScore->startTime();
	}

	return true;
}

void GameScene::finalize() const
{
	_implGame->finalize();
}

void GameScene::draw() const
{
	if (!_pauseFlag) _implGame->draw();
	DrawBox(0, 0, Define::GAME_WIN_X2 + 2, Define::GAME_WIN_Y1 - 1, GetColor(0, 0, 0), true);
	_implScore->draw();

	DrawBox(Define::GAME_WIN_X1 - 1, Define::GAME_WIN_Y1 - 1, Define::GAME_WIN_X2 + 2, Define::GAME_WIN_Y2 + 1, GetColor(255, 255, 255), false);
	DrawBox(Define::GAME_WIN_X3 - 2, Define::GAME_WIN_Y3 - 2, Define::GAME_WIN_X4 + 2, Define::GAME_WIN_Y4 + 2, GetColor(255, 255, 255), false);
	DrawBox(Define::GAME_WIN_X5 - 2, Define::GAME_WIN_Y5 - 2, Define::GAME_WIN_X6 + 2, Define::GAME_WIN_Y6 + 2, GetColor(255, 255, 255), false);

	if (_pauseFlag)
	{
		int half_x = (Define::GAME_WIN_X2 - Define::GAME_WIN_X1) / 2;
		int quarter_y = (Define::GAME_WIN_Y2 - Define::GAME_WIN_Y1) / 4;
		DrawString(Define::GAME_WIN_X1 + half_x - 50, Define::GAME_WIN_Y1 + quarter_y, "-- PAUSE --", GetColor(255, 255, 255));
	}
}