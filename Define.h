#pragma once

#include <string>


class Define final {
public:
	const static int WIN_W;	//ウィンドウサイズ横
	const static int WIN_H;	//ウィンドウサイズ縦


	// Title画面
	const static int TITLE_X;
	const static int TITLE_Y;
	const static int TITLE_START_X;
	const static int TITLE_START_Y;
	const static int TITLE_INSTRUCT_X;
	const static int TITLE_INSTRUCT_Y;
	const static int TITLE_END_X;
	const static int TITLE_END_Y;

	// Game画面
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

	const static int GAME_SCORE_X;
	const static int GAME_SCORE_Y;
	const static int GAME_TIME_X;
	const static int GAME_TIME_Y;

	// 操作説明画面
	const static int INSTRUCT_X;
	const static int INSTRUCT_Y;

	// Result画面
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
};