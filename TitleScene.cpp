#include "TitleScene.h"
#include "Keyboard.h"
#include "eScene.h"
#include "Define.h"

#include <DxLib.h>

using namespace std;

TitleScene::TitleScene(IOnSceneChangedListener* impl, const Parameter& parameter) : AbstractScene(impl, parameter)
{
	this->initialize();
}

void TitleScene::initialize()
{
	_fontHandle = CreateFontToHandle(NULL, 8, 3);
	_nowSelect = 0;
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
			_implSceneChanged->onSceneChanged(eScene::Instruct, parameter, stackClear);
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
	DeleteFontToHandle(_fontHandle);
}

void TitleScene::draw() const
{
	DrawStringToHandle(Define::TITLE_X, Define::TITLE_Y,
		"■■■■■　■■■■　■■■■■　■■■　　■■■　　■■■\n"
		"　　■　　　■　　　　　　■　　　■　　■　　■　　■　　　\n"
		"　　■　　　■■■■　　　■　　　■■■　　　■　　　■■■\n"
		"　　■　　　■　　　　　　■　　　■　■　　　■　　　　　　■\n"
		"　　■　　　■■■■　　　■　　　■　　■　■■■　  ■■■"
		, GetColor(255, 255, 255), _fontHandle);

	DrawString(Define::TITLE_START_X, Define::TITLE_START_Y, "Start", GetColor(255, 255, 255));
	DrawString(Define::TITLE_INSTRUCT_X, Define::TITLE_INSTRUCT_Y, "Instructions", GetColor(255, 255, 255));
	DrawString(Define::TITLE_END_X, Define::TITLE_END_Y, "Exit", GetColor(255, 255, 255));

	switch (_nowSelect) {//現在の選択状態に従って処理を分岐
	case eTitleSelect::Start://スタート選択中なら
		DrawString(Define::TITLE_START_X, Define::TITLE_START_Y, "_____", GetColor(255, 255, 255));
		break;
	case eTitleSelect::Instructions://未実装選択中なら
		DrawString(Define::TITLE_INSTRUCT_X, Define::TITLE_INSTRUCT_Y, "____________", GetColor(255, 255, 255));
		break;
	case eTitleSelect::End://終了選択中なら
		DrawString(Define::TITLE_END_X, Define::TITLE_END_Y, "____", GetColor(255, 255, 255));
		break;
	}
}