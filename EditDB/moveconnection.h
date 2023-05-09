#ifndef MOVECONNECTION_H
#define MOVECONNECTION_H

#include <QDialog>
#include <QSqlDatabase>
#include <QTableWidget>

namespace Ui {
	class MoveConnection;
}

class MoveConnection : public QDialog
{
	Q_OBJECT
	QSqlDatabase m_db;

	void reload_Clients(QTableWidget& objTable);
	void reload_Shops_Choose(QTableWidget &objTable, int nSelectedClient, int nSelectedSity, bool bWithConnectionsOnly);
	void reload_Connections(QTableWidget &objTable, int nSelectedShop);
	void reload_Sities(QTableWidget &objTable, int nSelectedClient);

public:
	explicit MoveConnection(QSqlDatabase &db, QWidget *parent = nullptr);
	~MoveConnection();

private slots:
	void on_Cur_Connect_Client_cellClicked(int row);
	void on_Cur_Connect_Sity_cellClicked(int row);
	void on_Cur_Connect_Shop_cellClicked(int row);

	void on_Dest_Connect_Client_cellClicked(int row);
	void on_Dest_Connect_Sity_cellClicked(int row);
	void on_Dest_Connect_Shop_cellClicked(int row);

	void on_pushButton_Move_released();

private:
	Ui::MoveConnection *ui;
};

#endif // MOVECONNECTION_H
