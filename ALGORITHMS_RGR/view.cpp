#include "view.h"

#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <QTimer>
#include <QMessageBox>

View::View(QWidget *parent) :
	QMainWindow(parent)
{
	ui.setupUi(this);
	ui.centralWidget->setBaseSize(800, 800);
	//ui.horizontalSpacer->changeSize()
	this->setWindowTitle("Policeman&Bandit");
	QTimer* updater = new QTimer(this);
	updater->start(30);

	connect(ui.pbPlay, SIGNAL(clicked()), SLOT(pbPlayClicked()));
	connect(updater, SIGNAL(timeout()), SLOT(update()));
}

void View::setGame(Game* game)
{
	this->game = game;
}

void View::mousePressEvent(QMouseEvent *e)
{
	if (e->button() != Qt::LeftButton)
		return;

	if (!this->game->isActive() || !this->game->isPlayersTurn())
		return;

	this->realMousePosition = e->pos();
	int monsterIndex = this->game->getMonsterIndexOnPosition((e->pos() - QPoint(25, 25)) / 50);
	if (monsterIndex < 0)
		return;

	if (this->game->getMonsterType(monsterIndex) != this->game->getPlayMode())
		return;

	this->game->setSelectedMonsterIndex(monsterIndex);
}

void View::mouseMoveEvent(QMouseEvent *e)
{
	this->realMousePosition = e->pos();
	this->mousePosition = (e->pos() - QPoint(25, 25)) / 50;
}

void View::mouseReleaseEvent(QMouseEvent *e)
{
	if (e->button() != Qt::LeftButton)
		return;

	if (!this->game->isActive())
		return;

	this->realMousePosition = e->pos();
	this->game->moveSelectedMonsterToPosition((e->pos() - QPoint(25, 25)) / 50);
	this->game->setSelectedMonsterIndex(-1);

	Game::MonsterType winner;
	if (this->game->isGameOver(winner))
		QMessageBox::information(NULL, "Attention!", (winner == this->game->getPlayMode() ? "You win" : "Game over"));

}

void View::pbPlayClicked()
{
	this->ui.pbPlay->setText("Restart");

	this->game->setPlayMode(ui.rbBandit->isChecked() ? Game::MT_BANDIT : Game::MT_POLICEMEN);
	this->game->setAILevel(ui.sbAILevel->value());
	this->game->reset();
}

void View::paintEvent(QPaintEvent *)
{
	QPainter p(this);
	p.setPen(Qt::NoPen);

	//draw grid
	p.setPen(Qt::SolidLine);
	p.drawLine(400, 0, 400, 400);
	for (int i = 0; i < 8; i++)
	{
		// вертикальные линии
		p.drawLine(i * 50, 0, i * 50, 400);
		// горизонтальные линии
		p.drawLine(0, i * 50, 400, i * 50);
	}

	// шрифт для надписей
	QFont font = p.font();
	font.setPointSize(font.pointSize() * 2);
	p.setFont(font);

	//draw monsters
	for (int i = 0; i < this->game->getMonsterCount(); i++)
		if (i != this->game->getSelectedMonsterIndex())
		{
			p.setBrush(QBrush(QColor(255,255,255)));
			auto position = this->game->getMonsterPosition(i);
			p.drawEllipse(position * 50 + QPoint(25, 25), 20, 20);
			auto monster_title = this->game->getMonsterType(i) == Game::MT_POLICEMEN ? "P" : "B";
			p.drawText(position * 50 + QPoint(20, 33), monster_title);
		}

	// нарисуем препятствия
	//p.setBrush(QBrush(QColor(40, 40, 40)));
	for (int i = 0; i < game->stops_count; i++)
	{
		p.drawRect(game->stops[i].x() * 50, game->stops[i].y() * 50, 50, 50);
	}
	// TODO: пропадает буква при перемещении
	if (this->game->getSelectedMonsterIndex() >= 0)
		if (!(this->mousePosition.x() < 0 || this->mousePosition.y() < 0 || this->mousePosition.x() > 7 || this->mousePosition.y() > 7))
			if (this->game->canMoveToPosition(this->game->getSelectedMonsterIndex(), this->mousePosition))
			{
				p.setPen(QPen(QBrush(Qt::white), 5));
				p.setBrush(QBrush(QColor(210, 210, 210), Qt::NoBrush));
				p.drawRect(QRect(this->mousePosition * 50, QSize(50, 50)));
			}

	if (game->getSelectedMonsterIndex() >= 0)
	{
		p.setPen(Qt::NoPen);
		auto monster_title = this->game->getSelectedMonsterIndex() == Game::MT_POLICEMEN ? "P" : "B";
		p.drawEllipse(this->realMousePosition, 20, 20);
		p.setFont(font);
		p.drawText(this->realMousePosition, monster_title);
	}
}

