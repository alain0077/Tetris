#include "Define.h"

const int   Define::WIN_W = 300;		//ウィンドウサイズ横
const int   Define::WIN_H = 450;		//ウィンドウサイズ縦


//Title画面
const int Define::TITLE_X = Define::WIN_W / 10;
const int Define::TITLE_Y = Define::WIN_H / 6;
const int Define::TITLE_START_X = Define::WIN_W / 2 - 60;
const int Define::TITLE_START_Y = Define::WIN_H / 2;
const int Define::TITLE_INSTRUCT_X = Define::TITLE_START_X + 20;
const int Define::TITLE_INSTRUCT_Y = Define::TITLE_START_Y + 40;
const int Define::TITLE_END_X = Define::TITLE_INSTRUCT_X + 20;
const int Define::TITLE_END_Y = Define::TITLE_INSTRUCT_Y + 40;

//Game画面
const int Define::MINO_X = 15;
const int Define::MINO_Y = 14;
const int Define::MINO_COL_NUM = 12;
const int Define::MINO_ROW_NUM = 26;
const int Define::GAME_WIN_X1 = 20;
const int Define::GAME_WIN_Y1 = 50;
const int Define::GAME_WIN_X2 = Define::GAME_WIN_X1 + (Define::MINO_X * Define::MINO_COL_NUM);
const int Define::GAME_WIN_Y2 = Define::GAME_WIN_Y1 + (Define::MINO_Y * Define::MINO_ROW_NUM);

const int Define::GAME_WIN_X3 = Define::GAME_WIN_X2 + Define::MINO_X;
const int Define::GAME_WIN_Y3 = Define::GAME_WIN_Y1;
const int Define::GAME_WIN_X4 = Define::GAME_WIN_X3 + 4 * Define::MINO_X;
const int Define::GAME_WIN_Y4 = Define::GAME_WIN_Y3 + 4 * Define::MINO_Y;

const int Define::GAME_WIN_X6 = Define::GAME_WIN_X4;
const int Define::GAME_WIN_Y6 = Define::GAME_WIN_Y3 + (Define::MINO_Y * Define::MINO_ROW_NUM);
const int Define::GAME_WIN_X5 = Define::GAME_WIN_X3;
const int Define::GAME_WIN_Y5 = Define::GAME_WIN_Y6 - 4 * Define::MINO_Y;

const int Define::GAME_SCORE_X = Define::GAME_WIN_X1;
const int Define::GAME_SCORE_Y = Define::GAME_WIN_Y1 - 40;
const int Define::GAME_TIME_X = Define::GAME_WIN_X1;
const int Define::GAME_TIME_Y = Define::GAME_WIN_Y1 - 20;

// 操作説明画面
const int Define::INSTRUCT_X = Define::WIN_W / 2 - 40;
const int Define::INSTRUCT_Y = Define::WIN_H / 5;

//Result画面
const int Define::Result_Score_X = 200;
const int Define::Result_Score_Y = 80;
const int Define::Result_Restart_X = 50;
const int Define::Result_Restart_Y = 80;
const int Define::Result_Title_X = 50;
const int Define::Result_Title_Y = 80;