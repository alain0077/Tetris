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
	
	if (!_implGame->update()) {
		Parameter param;
		const bool stackClear = true;

		param.set("ParameterTagResultScore", _implScore->getFilalScore());
		param.set("ParameterTagTime", _implScore->getTime());

		_implSceneChanged->onSceneChanged(eScene::Result, param, stackClear);
	}

	return true;
}

void GameScene::finalize() const
{
	_implGame->finalize();
}

void GameScene::draw() const
{
	_implGame->draw();
	_implScore->draw();

	DrawBox(Define::GAME_WIN_X1 - 1, Define::GAME_WIN_Y1 - 1, Define::GAME_WIN_X2 + 2, Define::GAME_WIN_Y2 + 1, GetColor(255, 255, 255), false);
	DrawBox(Define::GAME_WIN_X3 - 2, Define::GAME_WIN_Y3 - 2, Define::GAME_WIN_X4 + 2, Define::GAME_WIN_Y4 + 2, GetColor(255, 255, 255), false);
	DrawBox(Define::GAME_WIN_X5 - 2, Define::GAME_WIN_Y5 - 2, Define::GAME_WIN_X6 + 2, Define::GAME_WIN_Y6 + 2, GetColor(255, 255, 255), false);
}