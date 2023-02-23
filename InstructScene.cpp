#include "InstructScene.h"
#include <DxLib.h>
#include "Define.h"
#include "Keyboard.h"

using namespace std;

InstructScene::InstructScene(IOnSceneChangedListener* impl, const Parameter& parameter) : AbstractScene(impl, parameter)
, _cnt(0)
{
}

bool InstructScene::update()
{
	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_RETURN) == 1) {
		Parameter parameter;
		const bool stackClear = true;
		_implSceneChanged->onSceneChanged(eScene::Title, parameter, stackClear);
	}

	_cnt++;

	return true;
}

void InstructScene::draw() const
{
	int color = GetColor(255, 255, 255);
	int x = Define::INSTRUCT_X - 35;

	DrawString(Define::INSTRUCT_X, Define::INSTRUCT_Y, "操作方法", color);
	DrawString(x, Define::INSTRUCT_Y + 40, "　左移動：←，A", color);
	DrawString(x, Define::INSTRUCT_Y + 60, "　右移動：→，D", color);
	DrawString(x, Define::INSTRUCT_Y + 80, "落下加速：↓，S", color);
	DrawString(x, Define::INSTRUCT_Y + 100, "　　回転：SPACE", color);
	DrawString(x, Define::INSTRUCT_Y + 120, "ストック：LSHIFT", color);
	DrawString(x, Define::INSTRUCT_Y + 140, "一時停止：ESCAPE", color);

	if(_cnt % 80 < 40) DrawString(x - 35, Define::INSTRUCT_Y + 220, "Enterキーを押してください．", color);
}