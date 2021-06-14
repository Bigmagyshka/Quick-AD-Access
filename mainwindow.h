#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Containers/client.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QSqlDriver>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT
	QString path, path_normal;
	Client *Clients;
	QSqlDatabase db;

public:
	MainWindow(QWidget *parent);
	MainWindow();

	void set_path (QString P){
		path = P + "/AnyDesk.exe ";
		path_normal = P;
	}

	bool read_DB();


	~MainWindow();

public slots:
	void open_connect();
	void Reload_DB();

private slots:
	void on_Menu_1_triggered();

private:
	Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
