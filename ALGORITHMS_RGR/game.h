#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QPoint>
#include <QQueue>
#include <QList>

#define MIN_VALUE 0
#define MAX_VALUE 255
#define EPIC_BIG_VALUE 500

class Game
{
public:
	Game();

	enum MonsterType {
		MT_NO_ONE = 0,
		MT_BANDIT = 1,
		MT_POLICEMAN = 2
	};

	void setActive(bool active) { this->active = active; }
	bool isActive() { return this->active; }

	void setPlayMode(MonsterType gameMode) { this->gameMode = gameMode; }
	void setArenaSize(int m, int n) { this->m = m; this->n = n; }
	QPoint getArenaSize() { return QPoint(m, n); }
	int getMonsterCount() { return 2; }
	MonsterType getPlayMode() { return this->gameMode; }

	QPoint& getBanditPosition() { return bandit; }
	QPoint& getPolicemanPosition()
	{
		return policeman;
	}

	bool checkRange(int x, int y) { return (x >= 0 && y >= 0 && x < n && y < m); }
	bool checkRange(const QPoint& point) { return checkRange(point.x(), point.y()); }

	QPoint& getMonsterPosition(int monsterIndex)
	{
		if (monsterIndex == 0)
			return getBanditPosition();
		else
			return getPolicemanPosition();
	}

	MonsterType getMonsterType(int monsterIndex)
	{
		if (monsterIndex == 0)
			return MT_BANDIT;
		else
			return MT_POLICEMAN;
	}

	int getSelectedMonsterIndex() { return selectedMonster; }
	void setSelectedMonsterIndex(int monsterIndex) { this->selectedMonster = monsterIndex; }
	int isPlayersTurn() { return playersTurn; }

	void reset();

	int getMonsterIndexOnPosition(const QPoint& pos);

	bool canMoveToPosition(int monsterIndex, const QPoint& pos);

	bool moveSelectedMonsterToPosition(const QPoint& pos);

	bool isGameOver(MonsterType& winner);
	bool isGameOver() { MonsterType winner; return isGameOver(winner); }
	QPoint* stops; // препятствия
	int stops_count = 7;

private:
	static const int NOT_INITIALIZED = 255;

	static const int STOP = 256;
	static const int EMPTY = 0;
	static const int BANDIT = 1;
	static const int POLICEMEN = 255;

	QPoint policeman;
	QPoint bandit;

	MonsterType gameMode;


	// размеры поля
	int m;
	int n;

	std::vector<std::vector<int>> map;
	QQueue<QPoint> searchWay;
	QPoint possibleMoves[8];

	bool active = false;
	bool playersTurn;
	int selectedMonster;

	void initialize();

	bool canMove(int x, int y);
	bool canMove(const QPoint& point) { return canMove(point.x(), point.y()); }

	void breath_search_bandit();

	void play();

	void prepareMap();
};

#endif // GAME_H
