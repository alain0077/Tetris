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

	DrawString(Define::INSTRUCT_X, Define::INSTRUCT_Y, "������@", color);
	DrawString(x, Define::INSTRUCT_Y + 40, "�@���ړ��F���CA", color);
	DrawString(x, Define::INSTRUCT_Y + 60, "�@�E�ړ��F���CD", color);
	DrawString(x, Define::INSTRUCT_Y + 80, "���������F���CS", color);
	DrawString(x, Define::INSTRUCT_Y + 100, "�@�@��]�FSPACE", color);
	DrawString(x, Define::INSTRUCT_Y + 120, "�X�g�b�N�FLSHIFT", color);
	DrawString(x, Define::INSTRUCT_Y + 140, "�ꎞ��~�FESCAPE", color);

	if(_cnt % 80 < 40) DrawString(x - 35, Define::INSTRUCT_Y + 220, "Enter�L�[�������Ă��������D", color);
}