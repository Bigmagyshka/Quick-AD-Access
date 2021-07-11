#include "mainwindow.h"
#include "start_window.h"
#include "edit_db.h"
#include <QApplication>
#include <QTimer>
#include <thread>


int main(int argc, char *argv[]){
//	setlocale(LC_ALL, "Russian");

	QApplication a(argc, argv);

	QString Folder = argv[0];
	Folder = Folder.left(Folder.lastIndexOf(QChar('\\')));

	start_Window Start;
	Start.set_pic(Folder, "Version: 0.71");
	Start.start(2.5);

	MainWindow *w = new MainWindow;
	w->set_path(Folder);
	w->read_DB();
	w->show();

	return a.exec();
}
