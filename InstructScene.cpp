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
	DrawString(Define::WIN_W / 2, 20, "������@", color);
	DrawString(Define::WIN_W / 2, 40, "�@���ړ��G���CA", color);
	DrawString(Define::WIN_W / 2, 60, "�@�E�ړ��G���CD", color);
	DrawString(Define::WIN_W / 2, 80, "���������G���CS", color);
	DrawString(Define::WIN_W / 2, 100, "�@�@��]�FSPACE", color);
	DrawString(Define::WIN_W / 2, 120, "�X�g�b�N�FLSHIFT", color);

	DrawString(Define::WIN_W / 2, 140, "Return�L�[�������Ă��������D", color);
}