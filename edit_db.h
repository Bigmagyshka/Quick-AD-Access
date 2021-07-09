#ifndef EDIT_DB_H
#define EDIT_DB_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QSqlDriver>

#include "My_error.h"

namespace Ui {
class edit_DB;
}

class edit_DB : public QDialog
{
	Q_OBJECT

public:
	explicit edit_DB(QWidget *parent = nullptr);
	edit_DB (QSqlDatabase &db);
	~edit_DB();
	void reload_Clients();
	void reload_Sities(int tab);
	void reload_Shops_Choose();
	void reload_Connections();
	void reload_Workers();

	int chosen_client = -1, chosen_sity = -1;
	int connect_client = -1, connect_sity = -1, connect_shop = -1;
	int worker_client = -1, worker_sity = -1, worker_shop = -1;

private slots:
	void on_DB_Clients_cellChanged(int row, int column);

	void on_Add_Client_clicked();

	void on_Add_Sity_clicked();

	void on_DB_Sities_cellChanged(int row, int column);

	void on_Choose_Client1_cellClicked(int row);

	void on_Choose_Sity1_cellClicked(int row);

	void on_Choose_Shop1_cellChanged(int row, int column);

	void on_Add_Shop_clicked();

	void on_Connect_Client_cellClicked(int row);

	void on_Connect_Sity_cellClicked(int row);

	void on_Connect_Shop_cellClicked(int row);

	void on_Connections_cellChanged(int row, int column);

	void on_Add_Connection_clicked();

	void on_Workers_Client_cellClicked(int row);

	void on_Workers_Sity_cellClicked(int row);

	void on_Workers_Shop_cellClicked(int row);

	void on_Workers_cellChanged(int row, int column);

	void on_Add_Worker_clicked();

private:
	Ui::edit_DB *ui;
	QSqlDatabase db;
	bool flag = false;
};

#endif // EDIT_DB_H
