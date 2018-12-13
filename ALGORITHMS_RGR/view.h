#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_view.h"

class view : public QMainWindow
{
	Q_OBJECT

public:
	view(QWidget *parent = Q_NULLPTR);

private:
	Ui::viewClass ui;
};
