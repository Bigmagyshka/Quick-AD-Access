#include "mainwindow.h"
#include "start_window.h"
#include "edit_db.h"
#include <QApplication>
#include <QTimer>
#include <thread>


int main(int argc, char *argv[]){
	QApplication a(argc, argv);

#ifdef QT_NO_DEBUG
	start_Window Start("Version: " + QString::number(QT_VERSION));
	Start.start(2.5);
#endif

	MainWindow w;
	w.read_DB();
	w.show();

	return a.exec();
}
