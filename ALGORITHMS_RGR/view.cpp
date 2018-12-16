#include "view.h"

#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <QTimer>
#include <QMessageBox>

int sq_size = 0;

View::View(QWidget *parent) :
	QMainWindow(parent)
{
	ui.setupUi(this);
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
	int monsterIndex = this->game->getMonsterIndexOnPosition((e->pos() - QPoint(sq_size/2, sq_size/2)) / sq_size);
	if (monsterIndex < 0)
		return;

	if (this->game->getMonsterType(monsterIndex) != this->game->getPlayMode())
		return;

	this->game->setSelectedMonsterIndex(monsterIndex);
}

void View::mouseMoveEvent(QMouseEvent *e)
{
	this->realMousePosition = e->pos();
	this->mousePosition = (e->pos() - QPoint(sq_size / 2, sq_size / 2)) / sq_size;
}

void View::mouseReleaseEvent(QMouseEvent *e)
{
	if (e->button() != Qt::LeftButton)
		return;

	if (!this->game->isActive())
		return;

	this->realMousePosition = e->pos();
	this->game->moveSelectedMonsterToPosition((e->pos() - QPoint(sq_size / 2, sq_size / 2)) / sq_size);
	this->game->setSelectedMonsterIndex(-1);

	Game::MonsterType winner;
	if (this->game->isGameOver(winner))
		QMessageBox::information(NULL, "Attention!", (winner == this->game->getPlayMode() ? "You win" : "Game over"));

}

void View::pbPlayClicked()
{
	int m = ui.m_lineEdit->text().toInt();
	int n = ui.n_lineEdit->text().toInt();
	if (m > 0 && n > 0)
	{
		game->setActive(true);
		this->game->setArenaSize(m, n);
		this->ui.pbPlay->setText("Restart");
		this->game->setPlayMode(ui.rbBandit->isChecked() ? Game::MT_BANDIT : Game::MT_POLICEMAN);
		this->game->reset();
	}
}

void View::paintEvent(QPaintEvent *)
{
	if (!game->isActive())
		return;
	QPainter p(this);
	p.setPen(Qt::NoPen);

	//draw grid
	p.setPen(Qt::SolidLine);
	
	// рассчитаем размер строки
	int row_size = 800 / game->getArenaSize().x();
	int column_size = 800 / game->getArenaSize().y();
	sq_size = row_size > column_size ? column_size : row_size;

	// высота поля
	int height = sq_size * game->getArenaSize().x();

	// ширина поля
	int width = sq_size * game->getArenaSize().y();

	// нарисуем строки
	for (int i = 0; i < game->getArenaSize().x(); i++)
	{
		p.drawLine(0, i * sq_size, width, i * sq_size);
	}

	// нарисуем столбцы
	for (int i = 0; i < game->getArenaSize().y(); i++)
	{
		// вертикальные линии
		p.drawLine(i * sq_size, 0, i * sq_size, height);
	}

	// граница последнего собца
	p.drawLine(width, 0, width, height);

	// шрифт для надписей
	QFont font = p.font();
	font.setPointSize(sq_size / 5 * 2);
	p.setFont(font);

	//draw monsters
	for (int i = 0; i < this->game->getMonsterCount(); i++)
		if (i != this->game->getSelectedMonsterIndex())
		{
			p.setBrush(QBrush(QColor(255,255,255)));
			auto position = this->game->getMonsterPosition(i);
			p.drawEllipse(position * sq_size + QPoint(sq_size/2, sq_size/2), sq_size / 5 * 2, sq_size / 5 * 2);
			auto monster_title = this->game->getMonsterType(i) == Game::MT_POLICEMAN ? "P" : "B";
			p.drawText(position * sq_size + QPoint(sq_size / 5 * 2, sq_size / 5 * 3), monster_title);
		}

	// нарисуем препятствия
	p.setBrush(QBrush(QColor(0, 0, 0)));
	for (int i = 0; i < game->stops_count; i++)
	{
		p.drawRect(game->stops[i].x() * sq_size, game->stops[i].y() * sq_size, sq_size, sq_size);
	}

	if (this->game->getSelectedMonsterIndex() >= 0)
		if (!(this->mousePosition.x() < 0 || this->mousePosition.y() < 0 || this->mousePosition.x() > width || this->mousePosition.y() > height))
			if (this->game->canMoveToPosition(this->game->getSelectedMonsterIndex(), this->mousePosition))
			{
				p.setPen(QPen(QBrush(Qt::white), 5));
				p.setBrush(QBrush(QColor(210, 210, 210), Qt::NoBrush));
				p.drawRect(QRect(this->mousePosition * sq_size, QSize(sq_size, sq_size)));
			}

	p.setBrush(QBrush(QColor(255, 255, 255)));
	if (game->getSelectedMonsterIndex() >= 0)
	{
		p.setPen(QColor(256, 256, 256));
		auto monster_title = this->game->getSelectedMonsterIndex() == Game::MT_POLICEMAN ? "P" : "B";
		p.drawEllipse(this->realMousePosition, sq_size / 5 * 2, sq_size / 5 * 2);
		p.setFont(font);
		p.drawText(this->realMousePosition, monster_title);
	}
}

