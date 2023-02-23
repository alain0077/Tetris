#include "SceneMgr.h"
#include "TitleScene.h"
#include "InstructScene.h"
#include "GameScene.h"
#include "ResultScene.h"

using namespace std;

SceneMgr::SceneMgr()
{
	Parameter parameter;
	_sceneStack.push(make_shared<TitleScene>(this, parameter)); //タイトル画面シーンを作ってpush
}
/*!
@brief スタックのトップのシーンの処理をする
*/
bool SceneMgr::update()
{
	//スタックのトップのシーンを更新
	if (!_sceneStack.top()->update()) return false;

	//スタックのトップのシーンを描画
	_sceneStack.top()->draw();
	
	return true;
}

/*!
@brief シーン変更(各シーンからコールバックされる)
@param scene 変更するシーンのenum
@param parameter 前のシーンから引き継ぐパラメータ
@param stackClear 現在のシーンのスタックをクリアするか
*/
void SceneMgr::onSceneChanged(const eScene scene, const Parameter& parameter, const bool stackClear)
{
	if (stackClear) {
		while (!_sceneStack.empty()) {
			_sceneStack.pop();
		}
	}
	switch (scene) {
	case Title:
		_sceneStack.push(make_shared<TitleScene>(this, parameter));
		break;
	case Game:
		_sceneStack.push(make_shared<GameScene>(this, parameter));
		break;
	case Instruct:
		_sceneStack.push(make_shared<InstructScene>(this, parameter));
		break;
	case Result:
		_sceneStack.push(make_shared<ResultScene>(this, parameter));
		break;
	default:
		// エラー処理
		break;
	}
}