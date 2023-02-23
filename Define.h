#pragma once

#include <string>


class Define final {
public:
	const static int WIN_W;	//ウィンドウサイズ横
	const static int WIN_H;	//ウィンドウサイズ縦


	//Title画面
	const static int START_X;
	const static int START_Y;
	const static int INSTRUCTIONS_X;
	const static int INSTRUCTIONS_Y;
	const static int END_X;
	const static int END_Y;

	//Game画面
	const static int GAME_WIN_X1;
	const static int GAME_WIN_Y1;
	const static int GAME_WIN_X2;
	const static int GAME_WIN_Y2;
	const static int GAME_WIN_X3;
	const static int GAME_WIN_Y3;
	const static int GAME_WIN_X4;
	const static int GAME_WIN_Y4;
	const static int GAME_WIN_X5;
	const static int GAME_WIN_Y5;
	const static int GAME_WIN_X6;
	const static int GAME_WIN_Y6;

	const static int MINO_X;
	const static int MINO_Y;
	const static int MINO_COL_NUM;
	const static int MINO_ROW_NUM;


	//Result画面
	const static int Result_Score_X;
	const static int Result_Score_Y;
	const static int Result_Restart_X;
	const static int Result_Restart_Y;
	const static int Result_Title_X;
	const static int Result_Title_Y;

	enum eResultSelect {
		Restart,
		Title,

		ResultNum,
	};

	//フレーム
	const static int FRAME;
};