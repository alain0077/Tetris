#include <DxLib.h>
#include "SystemMain.h"
#include "Define.h"
#include "SceneMgr.h"
#include "Keyboard.h"

/*!
* @brief DXライブラリやゲームの初期処理
*/
bool SystemMain::initialize() const
{
	SetAlwaysRunFlag(TRUE);						//ウィンドウがノンアクティブでも実行
	SetWindowSizeChangeEnableFlag(TRUE);		//ウィンドウサイズを自由に変更できるようにする
	SetOutApplicationLogValidFlag(FALSE);		//ログ出力しない
	SetFullScreenResolutionMode(DX_FSRESOLUTIONMODE_DESKTOP);	//フルスクリーン時に縦横比を維持する
	SetWindowText("Shooting Game");				//ウィンドウタイトルを付ける
	ChangeWindowMode(TRUE);						//ウィンドウモードに変更
	SetWindowSizeExtendRate(2.5);				//ウィンドウサイズを変更したい時はここに倍率を指定する
	const int COLOR_BIT = 32;					//色のbit数。通常32で良いが軽くするなら16にする
	SetGraphMode(Define::WIN_W, Define::WIN_H, COLOR_BIT);		//ゲーム画面の解像度を設定する
	if (DxLib_Init()) {							//DXライブラリ初期化処理
		return false;							//異常終了したら即座にやめる
	}
	SetDrawScreen(DX_SCREEN_BACK);				//裏画面処理を設定する
	return true;
}

/*!
* @brief DXライブラリやゲームの終了処理
*/
void SystemMain::finalize() const
{

	DxLib_End();
}

/*!
* @brief メイン処理
*/
void SystemMain::main() const
{
	SceneMgr sceneMgr;
	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen()) {
		if (sceneMgr.update()) {
			// 更新処理を記述
			Keyboard::getIns()->update();   //キーボードの更新
		}
		else {
			break;
		}
	}
}