﻿#include "game.h"
#include "qmath.h"

Game::Game()
	:active(false), selectedMonster(-1)
{
	//по диагонали
	possibleMoves[0] = QPoint(-1, +1);  //влево вниз
	possibleMoves[1] = QPoint(+1, +1);  //вправо вниз
	possibleMoves[2] = QPoint(-1, -1);  //влево вверх
	possibleMoves[3] = QPoint(+1, -1);  //вправо вверх


	possibleMoves[4] = QPoint(0, 1); // вниз
	possibleMoves[5] = QPoint(1, 0); // вправо
	possibleMoves[4] = QPoint(0, -1); // вверх
	possibleMoves[5] = QPoint(-1, 0); // влево


	initialize();
}

void Game::reset()
{
	this->active = true;
	initialize();

	if (this->gameMode != MT_BANDIT)
		runMinMax((gameMode == MT_BANDIT) ? MT_POLICEMEN : MT_BANDIT, 0, -EPIC_BIG_VALUE, +EPIC_BIG_VALUE);

	this->playersTurn = true;
}

int Game::getMonsterIndexOnPosition(const QPoint &pos)
{
	if (this->bandit == pos)
		return 0;

	for (int i = 0; i < 4; i++)
		if (this->wolfs[i] == pos)
			return i + 1;

	return -1;
}

bool Game::canMoveToPosition(int monsterIndex, const QPoint &pos)
{
	Q_ASSERT(monsterIndex >= 0 || monsterIndex <= 2);

	if (!checkRange(pos))
		return false;

	// нельзя ходить
	//if ((pos.x() + pos.y()) % 2 != 0)
	//	return false;

	QPoint oldPosition = getMonsterPosition(monsterIndex);
	QPoint diff = oldPosition - pos;
	//if (monsterIndex == POLICEMEN)
	//{
	//	if (abs(diff.x()) > 1 || abs(diff.y()) > 1)
	//		return false;
	//}
	//else if (monsterIndex == BANDIT)
	//{
	//	if (abs(diff.x()) == 1 && abs(diff.y()) == 0 || abs(diff.x()) == 0 && abs(diff.y()) == 1)
	//		return false;
	//}

	// дальше одной клетки
	if (abs(diff.x()) > 1 || abs(diff.y()) > 1)
		return false;

	// только диагональ
	if (abs(diff.x()) == 1 && abs(diff.y()) == 1 && !monsterIndex)
		return false;

	if (oldPosition == pos)
		return false;

	for (int i = 0; i < getMonsterCount(); i++)
		if (i != monsterIndex && getMonsterPosition(i) == pos)
			return false;

	return true;
}

bool Game::isGameOver(MonsterType& winner)
{
	winner = MT_NO_ONE;

	bool canMove = false;
	for (int k = 0; k < 4; k++)
		for (int i = 0; i < 2; i++)
			if (canMoveToPosition(k + 1, this->wolfs[k] + this->possibleMoves[i]))
				canMove = true;

	if (!canMove || this->bandit.y() == 0)
		winner = MT_BANDIT;

	canMove = false;
	for (int i = 0; i < 4; i++)
		if (canMoveToPosition(0, this->bandit + this->possibleMoves[i]))
			canMove = true;

	if (!canMove)
		winner = MT_POLICEMEN;

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
			this->wolfs[this->selectedMonster - 1] = pos;
	else
		return false;


	if (isGameOver())
		return true;

	this->playersTurn = !this->playersTurn;
	runMinMax(this->gameMode == MT_BANDIT ? MT_POLICEMEN : MT_BANDIT, 0, -EPIC_BIG_VALUE, +EPIC_BIG_VALUE);
	this->playersTurn = !this->playersTurn;

	isGameOver();
	return true;
}


void Game::prepareMap()
{
	for (int i = 0; i < 8; i++)
		memset(this->map[i], 0, 8 * sizeof(int));

	this->map[this->bandit.y()][this->bandit.x()] = BANDIT;
	for (int i = 0; i < 4; i++)
		this->map[this->wolfs[i].y()][this->wolfs[i].x()] = POLICEMEN;
}

//����� � ������, �������� ��������.
int Game::getHeuristicEvaluation()
{
	if (this->bandit.y() == 0)
		return 0;

	this->searchWay.clear();
	this->searchWay.enqueue(this->bandit);
	while (!this->searchWay.empty())
	{
		QPoint currentPosition = this->searchWay.dequeue(); //current position
		for (int i = 0; i < 4; i++)
			if (canMove(currentPosition + possibleMoves[i]))
			{
				QPoint newPosition = currentPosition + possibleMoves[i]; //new position
				this->map[newPosition.y()][newPosition.x()] = this->map[currentPosition.y()][currentPosition.x()] + 1;
				this->searchWay.enqueue(newPosition);
			}
	}

	int min = MAX_VALUE;
	for (int i = 0; i < 4; i++)
		if ((this->map[0][i * 2] > MIN_VALUE) && (this->map[0][i * 2] < min))
			min = this->map[0][i * 2];

	return min - 1;
}

void Game::temporaryMonsterMovement(int monsterIndex, int x, int y)
{
	if (monsterIndex == 0)
	{
		this->map[this->bandit.y()][this->bandit.x()] = EMPTY;
		this->map[this->bandit.y() + y][this->bandit.x() + x] = BANDIT;
		this->bandit += QPoint(x, y);
	}
	else
	{
		this->map[this->wolfs[monsterIndex - 1].y()][this->wolfs[monsterIndex - 1].x()] = EMPTY;
		this->map[this->wolfs[monsterIndex - 1].y() + y][this->wolfs[monsterIndex - 1].x() + x] = POLICEMEN;
		this->wolfs[monsterIndex - 1] += QPoint(x, y);
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

int Game::runMinMax(MonsterType monster, int recursiveLevel, int alpha, int beta)
{
	if (recursiveLevel == 0)
		this->prepareMap();

	int test = NOT_INITIALIZED;

	//�� ��������� ������ ������ (�� ������) ���������� �������� ������� ���������
	if (recursiveLevel >= this->AILevel * 2)
	{
		int heuristic = getHeuristicEvaluation();
		prepareMap();
		return heuristic;
	}

	//������ ���������� ����. 0-7 - ��������� ���� ������, 8-11 - ��������� ���� �����
	int bestMove = NOT_INITIALIZED;

	bool isWolf = (monster == MT_POLICEMEN);
	int MinMax = isWolf ? MIN_VALUE : MAX_VALUE;

	//���������� ��� ��������� ���� ������� �������
	for (int i = (isWolf ? 0 : 8); i < (isWolf ? 8 : 12); i++)
	{
		int curMonster = isWolf ? i / 2 + 1 : 0;
		QPoint curMonsterPos = curMonster == 0 ? this->bandit : this->wolfs[curMonster - 1];
		QPoint curMove = this->possibleMoves[isWolf ? i % 2 : i % 4];

		if (canMove(curMonsterPos + curMove))
		{
			//...�����, ����� ���� ������������ ��������
			temporaryMonsterMovement(curMonster, curMove);

			//���������, ��������� ����� ���, ������� �� �������
			test = runMinMax(isWolf ? MT_BANDIT : MT_POLICEMEN, recursiveLevel + 1, alpha, beta);

			//... � ��������������� �������� ���������
			temporaryMonsterMovement(curMonster, -curMove);

			//���� �� ����� ����, ��� ���� �� ����� - ��������, ��� �� ������
			if ((test > MinMax && monster == MT_POLICEMEN) || (test <= MinMax && monster == MT_BANDIT) || (bestMove == NOT_INITIALIZED))
			{
				MinMax = test;
				bestMove = i;
			}

			if (isWolf)
				alpha = qMax(alpha, test);
			else
				beta = qMin(beta, test);

			if (beta < alpha)
				break;
		}
	}

	//��� ������������ ���������, ����� ������ ������ - ���������� ��������� ������������� �������.
	if (bestMove == NOT_INITIALIZED)
	{
		int heuristic = getHeuristicEvaluation();
		prepareMap();
		return heuristic;
	}

	//�� � ����������, �����, ���� ��� ������� ������ ���
	if (recursiveLevel == 0 && bestMove != NOT_INITIALIZED)
	{
		if (monster == MT_POLICEMEN)
			this->wolfs[bestMove / 2] += this->possibleMoves[bestMove % 2];
		else
			this->bandit += this->possibleMoves[bestMove % 4];
	}

	return MinMax;
}

void Game::initialize()
{
	this->wolfs[0] = QPoint(0, 0);
	this->wolfs[1] = QPoint(2, 0);
	this->wolfs[2] = QPoint(4, 0);
	this->wolfs[3] = QPoint(6, 0);

	this->bandit = QPoint(3, 7);
}
