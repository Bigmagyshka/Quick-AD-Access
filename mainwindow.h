#pragma once
#include <QMainWindow>
#include <QSqlDatabase>

class Client;

namespace Ui { class MainWindow; }

class MainWindow : public QMainWindow
{
	Q_OBJECT
	Client *Clients;
	QSqlDatabase db;

public:
	MainWindow(QWidget *parent);
	MainWindow();


	bool read_DB();


	virtual ~MainWindow();

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
