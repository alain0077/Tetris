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
	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_UP) == 1) {//上キーで選択を一つ上へ
		_nowSelect = (_nowSelect + (eTitleSelect::TitleNum - 1)) % eTitleSelect::TitleNum;
	}

	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_DOWN) == 1) {//下キーで選択を一つ下へ
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

	switch (_nowSelect) {//現在の選択状態に従って処理を分岐
	case eTitleSelect::Start://スタート選択中なら
		DrawString(Define::START_X, Define::START_Y, "_____", GetColor(255, 255, 255));
		break;
	case eTitleSelect::Instructions://未実装選択中なら
		DrawString(Define::INSTRUCTIONS_X, Define::INSTRUCTIONS_Y, "____________", GetColor(255, 255, 255));
		break;
	case eTitleSelect::End://終了選択中なら
		DrawString(Define::END_X, Define::END_Y, "____", GetColor(255, 255, 255));
		break;
	}
}