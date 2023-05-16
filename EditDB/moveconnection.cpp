#include "moveconnection.h"
#include "ui_moveconnection.h"

#include <QSqlQuery>
#include "My_error.h"

void MoveConnection::reload_Clients(QTableWidget &objTable){
	QSqlQuery Query(m_db);

	objTable.setRowCount(0);

	Query.exec("SELECT * FROM Clients ORDER BY Clients.Name");
	while (Query.next()){
		objTable.insertRow(objTable.rowCount());
		objTable.setItem(objTable.rowCount()-1, 0, new QTableWidgetItem(Query.value(0).toString()));
		objTable.setItem(objTable.rowCount()-1, 1, new QTableWidgetItem(Query.value(1).toString()));
	}
}

void MoveConnection::reload_Shops_Choose(QTableWidget &objTable, int nSelectedClient, int nSelectedSity, bool bWithConnectionsOnly){
	QSqlQuery Query(m_db);
	objTable.setRowCount(0);

	if(nSelectedClient < 0 || nSelectedSity < 0)
		return;

	QString sQuery = "select id, Address from Shops where Owner_id = " + QString::number(nSelectedClient) + " and Sity_id = " + QString::number(nSelectedSity);
	if(bWithConnectionsOnly)
		sQuery += " and id in (select Shop_id from Work_Places where Shop_id in "
				  "(select id from Shops where Owner_id = " +  QString::number(nSelectedClient) + " and Sity_id = " + QString::number(nSelectedSity) +"))";
	sQuery += " ORDER BY Address";

	Query.exec(sQuery);

	while (Query.next()){
		objTable.insertRow(objTable.rowCount());
		objTable.setItem(objTable.rowCount()-1, 0, new QTableWidgetItem(Query.value(0).toString()));
		objTable.setItem(objTable.rowCount()-1, 1, new QTableWidgetItem(Query.value(1).toString()));
	}
}

void MoveConnection::reload_Connections(QTableWidget &objTable, int nSelectedShop){
	QSqlQuery Query(m_db);
	objTable.setRowCount(0);

	if(nSelectedShop < 0)
		return;

	Query.exec("SELECT * FROM Work_Places WHERE Work_Places.Shop_id = " + QString::number(nSelectedShop));
	while (Query.next()){
		objTable.insertRow(objTable.rowCount());
		objTable.setItem(objTable.rowCount()-1, 0, new QTableWidgetItem(Query.value(1).toBool()?"1":"0"));
		objTable.setItem(objTable.rowCount()-1, 1, new QTableWidgetItem(Query.value(2).toString()));
		objTable.setItem(objTable.rowCount()-1, 2, new QTableWidgetItem(Query.value(3).toString()));
		objTable.setItem(objTable.rowCount()-1, 3, new QTableWidgetItem(Query.value(4).toString()));
		objTable.setItem(objTable.rowCount()-1, 4, new QTableWidgetItem(Query.value(5).toBool()?"1":"0"));
	}
}

void MoveConnection::reload_Sities(QTableWidget &objTable, int nSelectedClient){
	QSqlQuery Query(m_db);
	objTable.setRowCount(0);

	if(nSelectedClient < 0)
		return;

	Query.exec("select * from Sities where id in (select Sity_id from Shops where Owner_id = " + QString::number(nSelectedClient) + ")");

	while (Query.next()){
		objTable.insertRow(objTable.rowCount());
		objTable.setItem(objTable.rowCount()-1, 0, new QTableWidgetItem(Query.value(0).toString()));
		objTable.setItem(objTable.rowCount()-1, 1, new QTableWidgetItem(Query.value(1).toString()));
	}
}

MoveConnection::MoveConnection(QSqlDatabase &db, QWidget *parent) :
	QDialog(parent), m_db(db), ui(new Ui::MoveConnection)
{
	if(!m_db.open()) {
		My_Error error("DB is offline");
		error.exec();
		close();
	}

	ui->setupUi(this);
	ui->Cur_Connect_Client->setColumnWidth(0, 7);
	ui->Cur_Connect_Sity->setColumnWidth(0, 7);
	ui->Cur_Connect_Shop->setColumnWidth(0, 7);
	ui->Cur_Connections->setColumnWidth(0, 7);

	ui->Dest_Connect_Client->setColumnWidth(0, 7);
	ui->Dest_Connect_Sity->setColumnWidth(0, 7);
	ui->Dest_Connect_Shop->setColumnWidth(0, 7);
	ui->Dest_Connections->setColumnWidth(0, 7);

	reload_Clients(*ui->Cur_Connect_Client);
	reload_Clients(*ui->Dest_Connect_Client);
}

MoveConnection::~MoveConnection()
{
	delete ui;
	m_db.close();
}

void MoveConnection::on_Cur_Connect_Client_cellClicked(int row)
{
	auto pItem = ui->Cur_Connect_Client->item(row,0);
	if(!pItem)
		return;

	auto nSelectedClient = pItem->text().toInt();
	reload_Sities(*ui->Cur_Connect_Sity, nSelectedClient);
	reload_Shops_Choose(*ui->Cur_Connect_Shop, -1, -1, false);
	reload_Connections(*ui->Cur_Connections, -1);
}


void MoveConnection::on_Cur_Connect_Sity_cellClicked(int row)
{
	auto pClientTable = ui->Cur_Connect_Client;
	auto pClientItem = pClientTable->item(pClientTable->currentRow(),0);
	if(!pClientItem)
		return;

	auto pSityItem = ui->Cur_Connect_Sity->item(row, 0);
	if(!pSityItem)
		return;

	auto nSelectedClient = pClientItem->text().toInt();
	auto nSelectedSity = pSityItem->text().toInt();

	reload_Shops_Choose(*ui->Cur_Connect_Shop, nSelectedClient, nSelectedSity, true);
	reload_Connections(*ui->Cur_Connections, -1);
}


void MoveConnection::on_Cur_Connect_Shop_cellClicked(int row)
{
	auto pItem = ui->Cur_Connect_Shop->item(row,0);
	if(!pItem)
		return;

	auto nSelectedShop = pItem->text().toInt();
	reload_Connections(*ui->Cur_Connections, nSelectedShop);
}

void MoveConnection::on_Dest_Connect_Client_cellClicked(int row)
{
	auto pItem = ui->Dest_Connect_Client->item(row,0);
	if(!pItem)
		return;

	auto nSelectedClient = pItem->text().toInt();
	reload_Sities(*ui->Dest_Connect_Sity, nSelectedClient);
	reload_Shops_Choose(*ui->Dest_Connect_Shop, -1, -1, false);
	reload_Connections(*ui->Dest_Connections, -1);
}


void MoveConnection::on_Dest_Connect_Sity_cellClicked(int row)
{
	auto pClientTable = ui->Dest_Connect_Client;
	auto pClientItem = pClientTable->item(pClientTable->currentRow(),0);
	if(!pClientItem)
		return;

	auto pSityItem = ui->Dest_Connect_Sity->item(row, 0);
	if(!pSityItem)
		return;

	auto nSelectedClient = pClientItem->text().toInt();
	auto nSelectedSity = pSityItem->text().toInt();

	reload_Shops_Choose(*ui->Dest_Connect_Shop, nSelectedClient, nSelectedSity, false);
	reload_Connections(*ui->Dest_Connections, -1);
}


void MoveConnection::on_Dest_Connect_Shop_cellClicked(int row)
{
	auto pItem = ui->Dest_Connect_Shop->item(row,0);
	if(!pItem)
		return;

	auto nSelectedShop = pItem->text().toInt();
	reload_Connections(*ui->Dest_Connections, nSelectedShop);
}


void MoveConnection::on_pushButton_Move_released()
{
	auto pConnectionTable = ui->Cur_Connections;
	auto pDestShopTable = ui->Dest_Connect_Shop;

	auto pConnectionItem = pConnectionTable->item(pConnectionTable->currentRow(),1);
	auto pDestShopItem = pDestShopTable->item(pDestShopTable->currentRow(),0);

	if(!pConnectionItem || !pDestShopItem)
		return;

	auto sConnection = pConnectionItem->text();
	auto sShopID = pDestShopItem->text();

	QSqlQuery Query(m_db);
	auto sQuery = "UPDATE Work_Places SET Shop_id= " + sShopID + " WHERE Connection= '" + sConnection + "';";
	Query.exec(sQuery);


	on_Cur_Connect_Shop_cellClicked(ui->Cur_Connect_Shop->currentRow());
	on_Dest_Connect_Shop_cellClicked(pDestShopTable->currentRow());
}

