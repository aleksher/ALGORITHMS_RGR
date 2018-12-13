#include "view.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	view w;
	w.show();
	return a.exec();
}
