#ifndef EDIT_DB_H
#define EDIT_DB_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QSqlDriver>

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
	void reload_Sities();
	void reload_Shops_Choose();

	int chosen_client, chosen_sity;

private slots:
	void on_DB_Clients_cellChanged(int row, int column);

	void on_Add_Client_clicked();

	void on_Add_Sity_clicked();

	void on_DB_Sities_cellChanged(int row, int column);

	void on_Choose_Client1_cellClicked(int row, int column);

	void on_Choose_Sity1_cellClicked(int row, int column);

	void on_Choose_Shop1_cellChanged(int row, int column);

	void on_Add_Shop_clicked();

private:
	Ui::edit_DB *ui;
	QSqlDatabase db;
	bool flag = false;
};

#endif // EDIT_DB_H
