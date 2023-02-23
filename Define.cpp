#include "Define.h"

const int   Define::WIN_W = 600;		//ウィンドウサイズ横
const int   Define::WIN_H = 680;		//ウィンドウサイズ縦


//Title画面
const int Define::START_X = 100;
const int Define::START_Y = 200;
const int Define::INSTRUCTIONS_X = 120;
const int Define::INSTRUCTIONS_Y = 240;
const int Define::END_X = 140;
const int Define::END_Y = 280;

//Game画面
const int Define::MINO_X = 15;
const int Define::MINO_Y = 14;
const int Define::MINO_COL_NUM = 12;
const int Define::MINO_ROW_NUM = 26;
const int Define::GAME_WIN_X1 = 20;
const int Define::GAME_WIN_Y1 = 90;
const int Define::GAME_WIN_X2 = 20 + (Define::MINO_X * Define::MINO_COL_NUM);
const int Define::GAME_WIN_Y2 = 90 + (Define::MINO_Y * Define::MINO_ROW_NUM);

const int Define::GAME_WIN_X3 = Define::GAME_WIN_X2 + Define::MINO_X;
const int Define::GAME_WIN_Y3 = Define::GAME_WIN_Y1;
const int Define::GAME_WIN_X4 = Define::GAME_WIN_X3 + 4 * Define::MINO_X;
const int Define::GAME_WIN_Y4 = Define::GAME_WIN_Y3 + 4 * Define::MINO_Y;

const int Define::GAME_WIN_X6 = Define::GAME_WIN_X4;
const int Define::GAME_WIN_Y6 = Define::GAME_WIN_Y3 + (Define::MINO_Y * Define::MINO_ROW_NUM);
const int Define::GAME_WIN_X5 = Define::GAME_WIN_X3;
const int Define::GAME_WIN_Y5 = Define::GAME_WIN_Y6 - 4 * Define::MINO_Y;

//Result画面
const int Define::Result_Score_X = 200;
const int Define::Result_Score_Y = 80;
const int Define::Result_Restart_X = 50;
const int Define::Result_Restart_Y = 80;
const int Define::Result_Title_X = 50;
const int Define::Result_Title_Y = 80;

//フレーム
const int Define::FRAME = 60;