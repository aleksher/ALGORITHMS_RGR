#ifndef VIEW_H
#define VIEW_H

#include <QTWidgets/QMainWindow>
#include <QTimer>
#include "game.h"
#include "ui_view.h"



class View : public QMainWindow
{
	Q_OBJECT

public:
	explicit View(QWidget *parent = 0);

	void setGame(Game* game);

protected:
	void paintEvent(QPaintEvent *);
	void mousePressEvent(QMouseEvent *e);
	void mouseReleaseEvent(QMouseEvent *e);
	void mouseMoveEvent(QMouseEvent *e);

private:
	Ui::View ui;
	Game* game;
	QPoint mousePosition;
	QPoint realMousePosition;

public slots:
	void pbPlayClicked();
};

#endif // VIEW_H
