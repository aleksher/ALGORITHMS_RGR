#include "game.h"
#include "qmath.h"

Game::Game()
	:active(false), selectedMonster(-1)
{
	//по диагонали
	possibleMoves[4] = QPoint(-1, +1);  //влево вниз
	possibleMoves[5] = QPoint(+1, +1);  //вправо вниз
	possibleMoves[6] = QPoint(-1, -1);  //влево вверх
	possibleMoves[7] = QPoint(+1, -1);  //вправо вверх


	possibleMoves[0] = QPoint(0, 1); // вниз
	possibleMoves[1] = QPoint(1, 0); // вправо
	possibleMoves[2] = QPoint(0, -1); // вверх
	possibleMoves[3] = QPoint(-1, 0); // влево


	initialize();
}

void Game::reset()
{
	this->active = true;
	initialize();

	play();

	this->playersTurn = true;
}

int Game::getMonsterIndexOnPosition(const QPoint &pos)
{
	if (this->bandit == pos)
		return 0;

	if (policeman == pos)
		return 1;

	return -1;
}

bool Game::canMoveToPosition(int monsterIndex, const QPoint &pos)
{
	Q_ASSERT(monsterIndex >= 0 || monsterIndex <= 2);

	if (!checkRange(pos) && getPlayMode() != MT_BANDIT)
		return false;

	QPoint oldPosition = getMonsterPosition(monsterIndex);
	QPoint diff = oldPosition - pos;

	// дальше одной клетки
	if (abs(diff.x()) > 1 || abs(diff.y()) > 1)
		return false;

	// запрет бандиту ходить на полицейского
	if (monsterIndex == 0 && this->policeman == pos)
	{
		return false;
	}

	// запрет бандиту ходить по диагонали
	if (abs(diff.x()) == 1 && abs(diff.y()) == 1 && monsterIndex == 0)
		return false;

	if (oldPosition == pos)
		return false;

	// проверка на поход по препятствиям
	for (int i = 0; i < stops_count; i++)
		if (stops[i] == pos)
			return false;

	return true;
}

bool Game::isGameOver(MonsterType& winner)
{
	winner = MT_NO_ONE;

	auto policeman_pos = getPolicemanPosition();
	auto bandit_pos = getBanditPosition();

	if (policeman_pos == bandit_pos)
	{
		winner = MT_POLICEMAN;
		return true;
	}

	if (!checkRange(bandit_pos))
	{
		winner = MT_BANDIT;
		return true;
	}

	if (winner != MT_NO_ONE)
	{
		this->active = false;
		return true;
	}

	return false;
}

bool Game::moveSelectedMonsterToPosition(const QPoint &pos)
{
	if (this->selectedMonster < 0)
		return false;

	if (canMoveToPosition(this->selectedMonster, pos))
		if (this->selectedMonster == 0)
			this->bandit = pos;
		else
			this->policeman = pos;
	else
		return false;


	if (isGameOver())
		return true;

	this->playersTurn = !this->playersTurn;
	play();
	this->playersTurn = !this->playersTurn;

	isGameOver();
	return true;
}

void Game::prepareMap()
{
	map.resize(m);
	for (int i = 0; i < m; i++)
		map[i].resize(n);

	this->map[this->bandit.y()][this->bandit.x()] = BANDIT;
	this->map[this->policeman.y()][this->policeman.x()] = POLICEMEN;
	for (int i = 0; i < stops_count; i++)
	{
		this->map[this->stops[i].y()][this->stops[i].x()] = STOP;
	}
}

void Game::breath_search_bandit()
{
	this->searchWay.clear();
	this->searchWay.enqueue(this->bandit);
	while (!this->searchWay.empty())
	{
		QPoint currentPosition = this->searchWay.dequeue();
		for (int i = 0; i < 4; i++)
		{
			auto res = currentPosition + possibleMoves[i];
			if (canMove(res))
			{
				this->map[res.y()][res.x()] = this->map[currentPosition.y()][currentPosition.x()] + 1;
				this->searchWay.enqueue(res);
			}
		}
	}
}


void Game::play()
{
	prepareMap();
	// заполним карту расстояниями
	breath_search_bandit();


	if (getPlayMode() == MT_BANDIT)
	{
		int min = MAX_VALUE;
		int movement_index = 0;
		for (int i = 0; i < 8; i++)
		{
			QPoint new_pos = this->policeman + this->possibleMoves[i];
			if (new_pos == this->bandit)
			{
				movement_index = i;
				break;
			}
			if (checkRange(new_pos) && map[new_pos.y()][new_pos.x()] < min)
			{
				min = map[new_pos.y()][new_pos.x()];
				movement_index = i;
			}
		}
		this->policeman += possibleMoves[movement_index];
	}
	else if (getPlayMode() == MT_POLICEMAN)
	{
		int max = MIN_VALUE;
		int movement_index = 0;
		for (int i = 0; i < 4; i++)
		{
			QPoint new_pos = this->bandit + this->possibleMoves[i];
			if (checkRange(new_pos))
			{
				if (map[new_pos.y()][new_pos.x()] > max && map[new_pos.y()][new_pos.x()] < 255)
				{
					max = map[new_pos.y()][new_pos.x()];
					movement_index = i;
				}
			}
			else
			{
				movement_index = i;
				break;
			}
		}
		this->bandit += possibleMoves[movement_index];
	}
}

void Game::initialize()
{
	if (!isActive())
		return;
	stops_count = m * n / 5;
	stops = new QPoint[stops_count];
	while ((this->policeman = QPoint(rand() % n, rand() % m)) == (this->bandit = QPoint(n / 4 + rand() % (n / 2), m / 4 + rand() % (m / 2))));
	for (int i = 0; i < stops_count; i++)
	{
		QPoint stop;
		bool flag = true;
		int count = 0;
		while (flag)
		{
			stop = QPoint(rand() % n, rand() % m);
			for (int j = 0; j < count; j++)
			{
				if (stops[j] != stop && stop != this->policeman && stop != this->bandit)
					flag = false;
			}
			count++;
		}
		this->stops[i] = stop;
	}
}

bool Game::canMove(int x, int y)
{
	if (!checkRange(x, y))
		return false;

	if (map[y][x] != EMPTY)
		return false;

	return true;
}

