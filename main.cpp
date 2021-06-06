#include "mainwindow.h"
#include "start_window.h"
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
	Start.set_pic(Folder, "Version: 0.5");
	Start.start(2.5);
}


int main(int argc, char *argv[]){
//	setlocale(LC_ALL, "Russian");
	QString Folder = "./debug";
	QApplication a(argc, argv);

	QString New_Folder = argv[0];
	New_Folder = New_Folder.left(New_Folder.lastIndexOf(QChar('\\')));

	Folder = New_Folder;

	start(Folder);


	MainWindow w;
	w.set_path(Folder);

	w.read_DB(Folder);


	w.show();
	return a.exec();
}
