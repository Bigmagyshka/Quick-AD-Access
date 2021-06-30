#include "mainwindow.h"
#include "start_window.h"
#include "edit_db.h"
#include <QApplication>
#include <QTimer>
#include <thread>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QSqlDriver>

void start(QString Folder){
	start_Window Start;
	Start.set_pic(Folder, "Version: 0.53b");
	Start.start(2.5);
}


int main(int argc, char *argv[]){
//	setlocale(LC_ALL, "Russian");

	QApplication a(argc, argv);

	QString Folder = argv[0];
	Folder = Folder.left(Folder.lastIndexOf(QChar('\\')));

//	start(Folder);

	MainWindow *w = new MainWindow;
	w->set_path(Folder);
	w->read_DB();
	w->show();

	return a.exec();
}
