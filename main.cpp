#include "qtqrcode.h"
#include <QtWidgets/QApplication>


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QtQRCode w;
	w.show();
	
	return a.exec();
}
