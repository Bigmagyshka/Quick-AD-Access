#pragma once
#include <QDialog>
#include <QSqlDatabase>

namespace Ui {class delete_db;}

class delete_db : public QDialog
{
	Q_OBJECT

public:
	explicit delete_db(QWidget *parent = nullptr);
	delete_db (QSqlDatabase &db);
	virtual ~delete_db();

	void reload_Clients();
	void reload_Sities();
	void reload_Shops();
	void reload_Connections();
	void reload_Workers();

	void delete_Shop(int a);

private slots:
	void on_Clients_cellClicked(int row);

	void on_Sities_cellClicked(int row);

	void on_Shops_cellClicked(int row);

	void on_Workers_cellClicked(int row);

	void on_Connections_cellClicked(int row);

	void on_Del_Connection_clicked();

	void on_Del_Worker_clicked();

	void on_Del_Shop_clicked();

	void on_Del_Sity_clicked();

	void on_Del_Client_clicked();

private:
	Ui::delete_db *ui;
	QSqlDatabase db;

	int Client = -1, Sity = -1, Shop = -1;
	QString Connection, Number;
};
