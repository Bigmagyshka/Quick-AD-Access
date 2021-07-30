#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QSqlDriver>
#include <thread>

#include "My_error.h"
#include "ask.h"
#include "edit_db.h"
#include "delete_db.h"
#include "Containers/Client.h"
#include "windows.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT
	Client *Clients;
	QSqlDatabase db;

public:
	MainWindow(QWidget *parent);
	MainWindow();


	bool read_DB();


	~MainWindow();

public slots:
	void open_connect();
	void Reload_DB();

private slots:
	void on_Menu_1_triggered();

	void on_Edit_DB_triggered();

	void on_Delete_From_DB_triggered();

private:
	Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
