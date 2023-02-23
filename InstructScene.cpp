#include "InstructScene.h"
#include <DxLib.h>
#include "Define.h"
#include "Keyboard.h"

using namespace std;

InstructScene::InstructScene(IOnSceneChangedListener* impl, const Parameter& parameter) : AbstractScene(impl, parameter)
, _NowSelect(0)
{
}

bool InstructScene::update()
{


	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_RETURN) == 1) {
		Parameter parameter;
		const bool stackClear = true;

		_implSceneChanged->onSceneChanged(eScene::Title, parameter, stackClear);
	}

	return true;
}

void InstructScene::draw() const
{
	int color = GetColor(255, 255, 255);
	DrawString(Define::WIN_W / 2, 20, "操作方法", color);
	DrawString(Define::WIN_W / 2, 40, "　左移動；←，A", color);
	DrawString(Define::WIN_W / 2, 60, "　右移動；→，D", color);
	DrawString(Define::WIN_W / 2, 80, "落下加速；↓，S", color);
	DrawString(Define::WIN_W / 2, 100, "　　回転：SPACE", color);
	DrawString(Define::WIN_W / 2, 120, "ストック：LSHIFT", color);

	DrawString(Define::WIN_W / 2, 140, "Returnキーを押してください．", color);
}