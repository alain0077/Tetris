#include "TitleScene.h"
#include "Keyboard.h"
#include "eScene.h"
#include "Define.h"

#include <DxLib.h>

using namespace std;

TitleScene::TitleScene(IOnSceneChangedListener* impl, const Parameter& parameter) : AbstractScene(impl, parameter),
_nowSelect(0)
{
}

void TitleScene::initialize()
{
}

bool TitleScene::update()
{
	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_UP) == 1) {//��L�[�őI��������
		_nowSelect = (_nowSelect + (eTitleSelect::TitleNum - 1)) % eTitleSelect::TitleNum;
	}

	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_DOWN) == 1) {//���L�[�őI���������
		_nowSelect = (_nowSelect + 1) % eTitleSelect::TitleNum;
	}

	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_RETURN) == 1) {
		Parameter parameter;
		const bool stackClear = false;

		switch (_nowSelect) {
		case eTitleSelect::Start:
			_implSceneChanged->onSceneChanged(eScene::Game, parameter, stackClear);
			break;
		case eTitleSelect::Instructions:
			//_implSceneChanged->onSceneChanged(eScene::Instruct, parameter, stackClear);
			break;
		case eTitleSelect::End:
			return false;
			break;
		}
	}

	return true;
}

void TitleScene::finalize() const
{
}

void TitleScene::draw() const
{
	DrawString(Define::START_X, Define::START_Y, "Start", GetColor(255, 255, 255));
	DrawString(Define::INSTRUCTIONS_X, Define::INSTRUCTIONS_Y, "Instructions", GetColor(255, 255, 255));
	DrawString(Define::END_X, Define::END_Y, "Exit", GetColor(255, 255, 255));

	switch (_nowSelect) {//���݂̑I����Ԃɏ]���ď����𕪊�
	case eTitleSelect::Start://�X�^�[�g�I�𒆂Ȃ�
		DrawString(Define::START_X, Define::START_Y, "_____", GetColor(255, 255, 255));
		break;
	case eTitleSelect::Instructions://�������I�𒆂Ȃ�
		DrawString(Define::INSTRUCTIONS_X, Define::INSTRUCTIONS_Y, "____________", GetColor(255, 255, 255));
		break;
	case eTitleSelect::End://�I���I�𒆂Ȃ�
		DrawString(Define::END_X, Define::END_Y, "____", GetColor(255, 255, 255));
		break;
	}
}