#include "Tetris.h"
#include "Keyboard.h"
#include "Define.h"

#include <DxLib.h>
#include <random>
#include <algorithm>

using namespace std;

int GetRand();
vector<shared_ptr<Obj>> CreateMino(int& type);
vector<pair<int, int>> MinoAngleInfo(int& type);

Tetris::Tetris(shared_ptr<IIncScoreListener> impl) : AbstractGame(),
_implScore(impl)
{
	this->initialize();
}

void Tetris::initialize()
{
	_field = vector<vector<shared_ptr<Obj>>>(Define::MINO_ROW_NUM, vector<shared_ptr<Obj>>(Define::MINO_COL_NUM, nullptr));
	_cnt = 0;

	_nowType = GetRand();
	_nowMino = CreateMino(_nowType);
	_nowAngle = eMinoAngle::Angle_0;
	_minoAngleInfo = MinoAngleInfo(_nowType);

	_nextType = GetRand();
	_nextMino = CreateMino(_nextType);

	_changeFlag = false;
	_keepType = eMinoType::MinoNum;
	_keepMino = vector<shared_ptr<Obj>>(4, nullptr);
}

void Tetris::finalize()
{
	_field.clear();
	_nowMino.clear();
	_nextMino.clear();
	_minoAngleInfo.clear();
}

bool Tetris::update()
{
	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_RIGHT) == 1 ||
		Keyboard::getIns()->getPressingCount(KEY_INPUT_D) == 1)
	{
		bool flag = false;

		for (int i = 0; i < _nowMino.size(); i++)
		{
			flag = IsHit(_nowMino[i]->_x + Define::MINO_X, _nowMino[i]->_y);
			
			if (flag) break;
		}

		if (!flag)
		{
			for (int i = 0; i < _nowMino.size(); i++)
			{
				_nowMino[i]->_x += Define::MINO_X;
			}
		}
	}
	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_LEFT) == 1 ||
		Keyboard::getIns()->getPressingCount(KEY_INPUT_A) == 1)
	{
		bool flag = false;

		for (int i = 0; i < _nowMino.size(); i++)
		{
			flag = IsHit(_nowMino[i]->_x - Define::MINO_X, _nowMino[i]->_y);

			if (flag) break;
		}

		if (!flag)
		{
			for (int i = 0; i < _nowMino.size(); i++)
			{
				_nowMino[i]->_x -= Define::MINO_X;
			}
		}
	}

	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_DOWN) >= 1 ||
		Keyboard::getIns()->getPressingCount(KEY_INPUT_S) >= 1)
	{
		bool flag = false;

		for (int i = 0; i < _nowMino.size(); i++)
		{
			if (_nowMino[i]->_y + 2 < 0) continue;

			flag = IsHit(_nowMino[i]->_x, _nowMino[i]->_y + 2);

			if (flag) break;
		}

		if (!flag)
		{
			for (int i = 0; i < _nowMino.size(); i++)
			{
				_nowMino[i]->_y += 2;
			}
		}
		else
		{
			flag = false;

			while (!flag)
			{
				for (int i = 0; i < _nowMino.size(); i++)
				{
					if (_nowMino[i]->_y + 1 < 0) continue;

					flag = IsHit(_nowMino[i]->_x, _nowMino[i]->_y + 1);

					if (flag) break;
				}

				if (!flag)
				{
					for (int i = 0; i < _nowMino.size(); i++)
					{
						_nowMino[i]->_y++;
					}
				}
			}
		}
	}

	bool flag = false;

	for (int i = 0; i < _nowMino.size(); i++)
	{
		if (_nowMino[i]->_y + 1 < 0) continue;

		flag = IsHit(_nowMino[i]->_x, _nowMino[i]->_y + 1);

		if (flag) break;
	}

	if (!flag)
	{
		for (int i = 0; i < _nowMino.size(); i++)
		{
			_nowMino[i]->_y += 1;
		}
	}
	else
	{
		bool game_over = false;

		for (int i = 0; i < _nowMino.size(); i++)
		{
			int col = _nowMino[i]->_x / Define::MINO_X;
			int row = (int)((_nowMino[i]->_y) / Define::MINO_Y);

			if (_nowMino[i]->_y < 0) return false;
			else _field[row][col] = _nowMino[i];
		}

		eraceLine();

		setNextMino();

		_changeFlag = false;
	}

	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_SPACE) == 1)
	{
		bool flag = false;
		int nextAngle = (_nowAngle + 1) % eMinoAngle::MinoAngleNum;
		int j = nextAngle * eMinoAngle::MinoAngleNum;

		for (int i = 0; i < _nowMino.size(); i++)
		{
			int x = _minoAngleInfo[i + j].first * Define::MINO_X;
			int y = _minoAngleInfo[i + j].second * Define::MINO_Y;

			flag = IsHit(_nowMino[i]->_x + x, _nowMino[i]->_y + y);

			if (flag) break;
		}

		if (!flag)
		{
			for (int i = 0; i < _nowMino.size(); i++)
			{
				int x = _minoAngleInfo[i + j].first * Define::MINO_X;
				int y = _minoAngleInfo[i + j].second * Define::MINO_Y;

				_nowMino[i]->_x += x;
				_nowMino[i]->_y += y;

				_nowAngle = nextAngle;
			}
		}
	}

	if (!_changeFlag && Keyboard::getIns()->getPressingCount(KEY_INPUT_LSHIFT ) == 1)
	{
		_changeFlag = true;

		if (_keepType == eMinoType::MinoNum)
		{
			_keepType = _nowType;
			_keepMino = CreateMino(_keepType);

			setNextMino();
		}
		else
		{
			swap(_nowType, _keepType);
			swap(_nowMino, _keepMino);

			_keepMino = CreateMino(_keepType);

			_nowAngle = eMinoAngle::Angle_0;
			_minoAngleInfo = MinoAngleInfo(_nowType);
		}
	}

	return true;
}

bool Tetris::IsHit(int x, int y)
{
	if (x < 0 || x > (Define::GAME_WIN_X2 - Define::MINO_X) - Define::GAME_WIN_X1) return true;
	else if (y < 0 || y >= (Define::GAME_WIN_Y2 - Define::MINO_Y) - Define::GAME_WIN_Y1) return true;

	int col = x / Define::MINO_X;
	int row = (int)(y / Define::MINO_Y);

	if (_field[row][col] != nullptr) return true;

	return false;
}

void Tetris::setNextMino()
{
	_nowType = _nextType;
	_nowMino = _nextMino;
	_nowAngle = eMinoAngle::Angle_0;
	_minoAngleInfo = MinoAngleInfo(_nowType);

	_nextType = GetRand();
	_nextMino = CreateMino(_nextType);
}

void Tetris::eraceLine()
{
	for (int i = 0; i < Define::MINO_ROW_NUM; i++)
	{
		bool flag = true;

		for (int j = 0; j < Define::MINO_COL_NUM; j++)
		{
			if (_field[i][j] == nullptr)
			{
				flag = false;
				break;
			}
		}

		if (flag)
		{
			for (int j = 0; j < i; j++)
			{
				for (int k = 0; k < Define::MINO_COL_NUM; k++)
				{
					if (_field[j][k] != nullptr) _field[j][k]->_y += Define::MINO_Y;
				}
			}

			for (int j = i; j > 0; j--) {
				_field[j] = _field[j - 1];
			}

			for(int j = 0; j < Define::MINO_COL_NUM; j++) _field[0][j] = nullptr;

			_implScore->IncScore(1000);
		}
	}
}

void Tetris::draw() const
{
	for (int i = 0; i < _nowMino.size(); i++)
	{
		DrawString(Define::GAME_WIN_X1 + _nowMino[i]->_x, Define::GAME_WIN_Y1 + _nowMino[i]->_y, "¡", _nowMino[i]->_color);
	}

	for (auto v : _field)
	{
		for (auto p : v)
		{
			if (p == nullptr) continue;
			DrawString(Define::GAME_WIN_X1 + p->_x, Define::GAME_WIN_Y1 + p->_y, "¡", p->_color);
		}
	}

	for (int i = 0; i < _nextMino.size(); i++)
	{
		int x = Define::GAME_WIN_X1 + _nextMino[i]->_x + ((Define::MINO_COL_NUM / 2 - 1) * Define::MINO_X);
		int y = Define::GAME_WIN_Y1 + _nextMino[i]->_y;

		DrawString(x + (4 * Define::MINO_X), y + (4 * Define::MINO_Y), "¡", _nextMino[i]->_color);
	}

	if (_keepType != eMinoType::MinoNum)
	{
		for (int i = 0; i < _keepMino.size(); i++)
		{
			int x = Define::GAME_WIN_X1 + _keepMino[i]->_x + ((Define::MINO_COL_NUM / 2 - 1) * Define::MINO_X);
			int y = Define::GAME_WIN_Y1 + _keepMino[i]->_y;

			DrawString(x + 4 * Define::MINO_X, y + (Define::MINO_ROW_NUM * Define::MINO_Y), "¡", _keepMino[i]->_color);
		}
	}
}

int GetRand()
{
	using dist_type = std::uniform_int_distribution<>;

	srand(GetNowCount() / (eMinoType::MinoNum));

	int num = rand();

	dist_type dist(0, eMinoType::MinoNum - 1);

	mt19937 mt(num);

	return dist(mt);
}

vector<shared_ptr<Obj>> CreateMino(int& type)
{
	int start_col = ((Define::MINO_COL_NUM / 2 - 1) * Define::MINO_X);
	int start_row = -Define::MINO_Y;

	int color = GetColor(255, 255, 255);

	vector<shared_ptr<Obj>> res;

	switch (type)
	{
	case eMinoType::TYPE_I:
		color = GetColor(0, 191, 255);

		res.push_back(make_shared<Obj>(color, start_col, start_row));
		res.push_back(make_shared<Obj>(color, start_col, start_row - Define::MINO_Y));
		res.push_back(make_shared<Obj>(color, start_col, start_row - (2 * Define::MINO_Y)));
		res.push_back(make_shared<Obj>(color, start_col, start_row - (3 * Define::MINO_Y)));

		return res;

	case eMinoType::TYPE_O:
		color = GetColor(255, 255, 0);

		res.push_back(make_shared<Obj>(color, start_col, start_row - Define::MINO_Y));
		res.push_back(make_shared<Obj>(color, start_col, start_row - (2 * Define::MINO_Y)));
		res.push_back(make_shared<Obj>(color, start_col + Define::MINO_X, start_row - Define::MINO_Y));
		res.push_back(make_shared<Obj>(color, start_col + Define::MINO_X, start_row - (2 * Define::MINO_Y)));

		return res;

	case eMinoType::TYPE_S:
		color = GetColor(0, 128, 0);

		res.push_back(make_shared<Obj>(color, start_col - Define::MINO_X, start_row - Define::MINO_Y));
		res.push_back(make_shared<Obj>(color, start_col, start_row - Define::MINO_Y));
		res.push_back(make_shared<Obj>(color, start_col, start_row - (2 * Define::MINO_Y)));
		res.push_back(make_shared<Obj>(color, start_col + Define::MINO_X, start_row - (2 * Define::MINO_Y)));

		return res;

	case eMinoType::TYPE_Z:
		color = GetColor(255, 0, 0);

		res.push_back(make_shared<Obj>(color, start_col - Define::MINO_X, start_row - (2 * Define::MINO_Y)));
		res.push_back(make_shared<Obj>(color, start_col, start_row - Define::MINO_Y));
		res.push_back(make_shared<Obj>(color, start_col, start_row - (2 * Define::MINO_Y)));
		res.push_back(make_shared<Obj>(color, start_col + Define::MINO_X, start_row - Define::MINO_Y));

		return res;

	case eMinoType::TYPE_J:
		color = GetColor(0, 0, 255);

		res.push_back(make_shared<Obj>(color, start_col, start_row - Define::MINO_Y));
		res.push_back(make_shared<Obj>(color, start_col + Define::MINO_X, start_row - Define::MINO_Y));
		res.push_back(make_shared<Obj>(color, start_col + Define::MINO_X, start_row - (2 * Define::MINO_Y)));
		res.push_back(make_shared<Obj>(color, start_col + Define::MINO_X, start_row - (3 * Define::MINO_Y)));

		return res;

	case eMinoType::TYPE_L:
		color = GetColor(255, 165, 0);

		res.push_back(make_shared<Obj>(color, start_col, start_row - Define::MINO_Y));
		res.push_back(make_shared<Obj>(color, start_col, start_row - (2 * Define::MINO_Y)));
		res.push_back(make_shared<Obj>(color, start_col, start_row - (3 * Define::MINO_Y)));
		res.push_back(make_shared<Obj>(color, start_col + Define::MINO_X, start_row - Define::MINO_Y));

		return res;

	case eMinoType::TYPE_T:
		color = GetColor(128, 0, 128);

		res.push_back(make_shared<Obj>(color, start_col - Define::MINO_X, start_row - (2 * Define::MINO_Y)));
		res.push_back(make_shared<Obj>(color, start_col, start_row - Define::MINO_Y));
		res.push_back(make_shared<Obj>(color, start_col, start_row - (2 * Define::MINO_Y)));
		res.push_back(make_shared<Obj>(color, start_col + Define::MINO_X, start_row - (2 * Define::MINO_Y)));

		return res;
	}

	return res;
}

vector<pair<int, int>> MinoAngleInfo(int& type)
{
	vector<pair<int, int>> res;

	switch (type)
	{
	case eMinoType::TYPE_I:
		// Angle_0
		res.push_back(make_pair(-2, 1));
		res.push_back(make_pair(-1, 0));
		res.push_back(make_pair(0, -1));
		res.push_back(make_pair(1, -2));

		// Angle_90
		res.push_back(make_pair(-1, -2));
		res.push_back(make_pair(0, -1));
		res.push_back(make_pair(1, 0));
		res.push_back(make_pair(2, 1));

		// Angle_180
		res.push_back(make_pair(2, -1));
		res.push_back(make_pair(1, 0));
		res.push_back(make_pair(0, 1));
		res.push_back(make_pair(-1, 2));

		// Angle_270
		res.push_back(make_pair(1, 2));
		res.push_back(make_pair(0, 1));
		res.push_back(make_pair(-1, 0));
		res.push_back(make_pair(-2, -1));

		return res;

	case eMinoType::TYPE_O:
		// Angle_0
		res.push_back(make_pair(0, 0));
		res.push_back(make_pair(0, 0));
		res.push_back(make_pair(0, 0));
		res.push_back(make_pair(0, 0));

		// Angle_90
		res.push_back(make_pair(0, 0));
		res.push_back(make_pair(0, 0));
		res.push_back(make_pair(0, 0));
		res.push_back(make_pair(0, 0));

		// Angle_180
		res.push_back(make_pair(0, 0));
		res.push_back(make_pair(0, 0));
		res.push_back(make_pair(0, 0));
		res.push_back(make_pair(0, 0));

		// Angle_270
		res.push_back(make_pair(0, 0));
		res.push_back(make_pair(0, 0));
		res.push_back(make_pair(0, 0));
		res.push_back(make_pair(0, 0));

		return res;

	case eMinoType::TYPE_S:
		// Angle_0
		res.push_back(make_pair(-2, -1));
		res.push_back(make_pair(-1, 0));
		res.push_back(make_pair(0, -1));
		res.push_back(make_pair(1, 0));

		// Angle_90
		res.push_back(make_pair(1, -2));
		res.push_back(make_pair(0, -1));
		res.push_back(make_pair(1, 0));
		res.push_back(make_pair(0, 1));

		// Angle_180
		res.push_back(make_pair(2, 1));
		res.push_back(make_pair(1, 0));
		res.push_back(make_pair(0, 1));
		res.push_back(make_pair(-1, 0));

		// Angle_270
		res.push_back(make_pair(-1, 2));
		res.push_back(make_pair(0, 1));
		res.push_back(make_pair(-1, 0));
		res.push_back(make_pair(0, -1));

		return res;

	case eMinoType::TYPE_Z:
		// Angle_0
		res.push_back(make_pair(-1, -2));
		res.push_back(make_pair(-1, 0));
		res.push_back(make_pair(0, -1));
		res.push_back(make_pair(0, 1));

		// Angle_90
		res.push_back(make_pair(2, -1));
		res.push_back(make_pair(0, -1));
		res.push_back(make_pair(1, 0));
		res.push_back(make_pair(-1, 0));

		// Angle_180
		res.push_back(make_pair(1, 2));
		res.push_back(make_pair(1, 0));
		res.push_back(make_pair(0, 1));
		res.push_back(make_pair(0, -1));

		// Angle_270
		res.push_back(make_pair(-2, 1));
		res.push_back(make_pair(0, 1));
		res.push_back(make_pair(-1, 0));
		res.push_back(make_pair(1, 0));

		return res;

	case eMinoType::TYPE_J:
		// Angle_0
		res.push_back(make_pair(-1, 0));
		res.push_back(make_pair(0, 1));
		res.push_back(make_pair(1, 0));
		res.push_back(make_pair(2, -1));

		// Angle_90
		res.push_back(make_pair(0, -1));
		res.push_back(make_pair(-1, 0));
		res.push_back(make_pair(0, 1));
		res.push_back(make_pair(1, 2));

		// Angle_180
		res.push_back(make_pair(1, 0));
		res.push_back(make_pair(0, -1));
		res.push_back(make_pair(-1, 0));
		res.push_back(make_pair(-2, 1));

		// Angle_270
		res.push_back(make_pair(0, 1));
		res.push_back(make_pair(1, 0));
		res.push_back(make_pair(0, -1));
		res.push_back(make_pair(-1, -2));

		return res;

	case eMinoType::TYPE_L:
		// Angle_0
		res.push_back(make_pair(-1, 0));
		res.push_back(make_pair(0, -1));
		res.push_back(make_pair(1, -2));
		res.push_back(make_pair(0, 1));

		// Angle_90
		res.push_back(make_pair(0, -1));
		res.push_back(make_pair(1, 0));
		res.push_back(make_pair(2, 1));
		res.push_back(make_pair(-1, 0));

		// Angle_180
		res.push_back(make_pair(1, 0));
		res.push_back(make_pair(0, 1));
		res.push_back(make_pair(-1, 2));
		res.push_back(make_pair(0, -1));

		// Angle_270
		res.push_back(make_pair(0, 1));
		res.push_back(make_pair(-1, 0));
		res.push_back(make_pair(-2, -1));
		res.push_back(make_pair(1, 0));

		return res;

	case eMinoType::TYPE_T:
		// Angle_0
		res.push_back(make_pair(-1, -2));
		res.push_back(make_pair(-1, 0));
		res.push_back(make_pair(0, -1));
		res.push_back(make_pair(1, 0));

		// Angle_90
		res.push_back(make_pair(2, -1));
		res.push_back(make_pair(0, -1));
		res.push_back(make_pair(1, 0));
		res.push_back(make_pair(0, 1));

		// Angle_180
		res.push_back(make_pair(1, 2));
		res.push_back(make_pair(1, 0));
		res.push_back(make_pair(0, 1));
		res.push_back(make_pair(-1, 0));

		// Angle_270
		res.push_back(make_pair(-2, 1));
		res.push_back(make_pair(0, 1));
		res.push_back(make_pair(-1, 0));
		res.push_back(make_pair(0, -1));

		return res;
	}

	return res;
}