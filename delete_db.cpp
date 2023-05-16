#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QSqlDriver>

#include "delete_db.h"
#include "ui_delete_db.h"
#include "My_error.h"
#include "ask.h"

bool Ask_me(QString Question){
	bool flag;
	ask Ask(flag,Question,"Нет","Да");
	Ask.exec();
	return flag;
}

delete_db::delete_db(QWidget *parent) : QDialog(parent), ui(new Ui::delete_db){
	ui->setupUi(this);
}

delete_db::delete_db(QSqlDatabase &db) : QDialog(), ui(new Ui::delete_db){

	ui->setupUi(this);
	setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
	setModal(true);
	this->m_db = db;
	if (db.open()){
		reload_Clients();
		reload_Sities();
	}

	ui->Clients->setColumnWidth(0,10);
	ui->Sities->setColumnWidth(0,10);
	ui->Sities->setColumnWidth(2,10);
	ui->Shops->setColumnWidth(0,10);
}

delete_db::~delete_db(){
	delete ui;
	m_db.close();
}

//Base Functions
void delete_db::reload_Clients(){
	QSqlQuery Query(m_db);
	ui->Clients->setRowCount(0);

	Query.exec("SELECT * FROM Clients ORDER BY Clients.Name");
	while (Query.next()){
		ui->Clients->insertRow(ui->Clients->rowCount());
		ui->Clients->setItem(ui->Clients->rowCount()-1, 0, new QTableWidgetItem(Query.value(0).toString()));
		ui->Clients->setItem(ui->Clients->rowCount()-1, 1, new QTableWidgetItem(Query.value(1).toString()));

	}
}

void delete_db::reload_Sities(){
	QSqlQuery Query(m_db);
	Query.exec("With my_count (ID , NAME , Shop_count) "
				"As ("
				"SELECT DISTINCT Sities.id, Sities.Name, sum(1) OVER(PARTITION BY Sities.Name) AS Shop_count FROM Shops "
				"JOIN Sities on Sities.id = Shops.Sity_id "
				"WHERE Shops.Owner_id = " + QString::number(Client)  +
				" ORDER BY Sities.Name"
				") "
				"SELECT DISTINCT ID, NAME, sum(Shop_count) OVER(PARTITION BY ID) AS № From ("
				"SELECT ID, NAME, Shop_count From my_count "
				"UNION SELECT Sities.id, Sities.Name, 0 AS Shop_count From Sities "
				") "
				"ORDER BY NAME"
				);
	ui->Sities->setRowCount(0);
	while (Query.next()){
		ui->Sities->insertRow(ui->Sities->rowCount());
		ui->Sities->setItem(ui->Sities->rowCount()-1, 0, new QTableWidgetItem(Query.value(0).toString()));
		ui->Sities->setItem(ui->Sities->rowCount()-1, 1, new QTableWidgetItem(Query.value(1).toString()));
		ui->Sities->setItem(ui->Sities->rowCount()-1, 2, new QTableWidgetItem(Query.value(2).toString()));
	}
}

void delete_db::reload_Shops(){
	QSqlQuery Query(m_db);

	ui->Shops->setRowCount(0);
	ui->Connections->setRowCount(0);
	ui->Workers->setRowCount(0);

	Query.exec("SELECT t1.id, t1.Address "
						"FROM Shops as t1 "
						"JOIN Clients as t2 on t1.Owner_id = t2.id "
						"JOIN Sities as t3 on t1.Sity_id = t3.id "
						" Where t2.id = " + QString::number(Client) +
						" AND t3.id = " + QString::number(Sity) + " ORDER BY t1.Address");

	while (Query.next()){
		ui->Shops->insertRow(ui->Shops->rowCount());
		ui->Shops->setItem(ui->Shops->rowCount()-1, 0, new QTableWidgetItem(Query.value(0).toString()));
		ui->Shops->setItem(ui->Shops->rowCount()-1, 1, new QTableWidgetItem(Query.value(1).toString()));
	}
}

void delete_db::reload_Connections(){
	QSqlQuery Query(m_db);
	Query.exec("SELECT * FROM Work_Places WHERE Work_Places.Shop_id = " + QString::number(Shop));

	ui->Connections->setRowCount(0);
	while (Query.next()){
		ui->Connections->insertRow(ui->Connections->rowCount());
		ui->Connections->setItem(ui->Connections->rowCount()-1, 0, new QTableWidgetItem(Query.value(1).toBool()?"1":"0"));
		ui->Connections->setItem(ui->Connections->rowCount()-1, 1, new QTableWidgetItem(Query.value(2).toString()));
		ui->Connections->setItem(ui->Connections->rowCount()-1, 2, new QTableWidgetItem(Query.value(3).toString()));
		ui->Connections->setItem(ui->Connections->rowCount()-1, 3, new QTableWidgetItem(Query.value(4).toString()));
		ui->Connections->setItem(ui->Connections->rowCount()-1, 4, new QTableWidgetItem(Query.value(5).toBool()?"1":"0"));
	}
}

void delete_db::reload_Workers(){
	QSqlQuery Query(m_db);
	Query.exec("SELECT * FROM Workers WHERE Workers.Shop_id = " + QString::number(Shop));
	ui->Workers->setRowCount(0);
	while (Query.next()){
		ui->Workers->insertRow(ui->Workers->rowCount());
		ui->Workers->setItem(ui->Workers->rowCount()-1, 0, new QTableWidgetItem(Query.value(1).toString()));
		ui->Workers->setItem(ui->Workers->rowCount()-1, 1, new QTableWidgetItem(Query.value(2).toString()));
		ui->Workers->setItem(ui->Workers->rowCount()-1, 2, new QTableWidgetItem(Query.value(3).toString()));
	}
}

void delete_db::delete_Shop(int a){
	QSqlQuery Query(m_db);
	Query.exec("DELETE FROM Workers WHERE Workers.Shop_id = " + QString::number(a));
	Query.exec("DELETE FROM Work_Places WHERE Work_Places.Shop_id = " + QString::number(a));
	Query.exec("DELETE FROM Shops WHERE Shops.id = " + QString::number(a));
}


//Tables Clicks
void delete_db::on_Clients_cellClicked(int row){
	QTableWidgetItem *item = ui->Clients->item(row,0);
	if (NULL != item) Client = item->text().toInt();
	Sity = -1;
	Shop = -1;
	Connection = "";
	Number = "";

	ui->Shops->setRowCount(0);
	ui->Connections->setRowCount(0);
	ui->Workers->setRowCount(0);

	reload_Sities();
}

void delete_db::on_Sities_cellClicked(int row){

	QTableWidgetItem *item = ui->Sities->item(row,0);
	if (NULL != item) Sity = item->text().toInt();
	Shop = -1;
	Connection = "";
	Number = "";

	reload_Shops();
}

void delete_db::on_Shops_cellClicked(int row){
	QTableWidgetItem *item = ui->Shops->item(row,0);
	if (NULL != item) Shop = item->text().toInt();
	Connection = "";
	Number = "";

	reload_Connections();
	reload_Workers();
}

void delete_db::on_Workers_cellClicked(int row){
	QTableWidgetItem *item = ui->Workers->item(row,1);
	if (NULL != item) Number = item->text();
}

void delete_db::on_Connections_cellClicked(int row){
	QTableWidgetItem *item = ui->Connections->item(row,1);
	if (NULL != item) Connection = item->text();
}


//Buttons
void delete_db::on_Del_Connection_clicked(){
	try {
		if (Connection.isEmpty()) throw "Connection not selected";

		if (!Ask_me("Это действие удалит Подключение, продолжить?")) {
			throw 1;
		}

		QSqlQuery Query(m_db);
		Query.exec("DELETE FROM Work_Places WHERE Work_Places.Connection = '" + Connection + "'");
		reload_Connections();
	}  catch (const char* a) {
		My_Error error(a);
		error.exec();
	}
	catch(int k){
	}

}

void delete_db::on_Del_Worker_clicked(){
	try {
		if (Number.isEmpty()) throw "Worker not selected";

		if (!Ask_me("Это действие удалит Работника, продолжить?")) {
			throw 1;
		}

		QSqlQuery Query(m_db);
		Query.exec("DELETE FROM Workers WHERE Workers.Number = '" + Number + "'");
		reload_Workers();
	}  catch (const char* a) {
		My_Error error(a);
		error.exec();
	}
	catch(int k){
	}
}

void delete_db::on_Del_Shop_clicked(){
	try {
		if (Shop == -1) throw "Shop not selected";

		if (!Ask_me("Это действие удалит Магазин, все подключения и работников, продолжить?")) {
			throw 1;
		}

		delete_Shop(Shop);
		Shop = -1;
		ui->Workers->setRowCount(0);
		ui->Connections->setRowCount(0);
		reload_Shops();
	}  catch (const char* a) {
		My_Error error(a);
		error.exec();
	}
	catch(int k){
	}
}

void delete_db::on_Del_Sity_clicked(){
	try {
		if (Sity == -1) throw "Sity not selected";

		if (!Ask_me("Это действие удалит ВСЕ магазины, подключения и работников в этом городе, продолжить?")) {
			throw 1;
		}

		QSqlQuery Query(m_db);
		Query.exec("SELECT DISTINCT t2.id FROM Shops as t2 "
							"JOIN Sities as t1 on t1.id = t2.Sity_id "
							"WHERE t2.Sity_id = " + QString::number(Sity));

		while(Query.next()){
			delete_Shop(Query.value(0).toInt());
		}

		Query.exec("DELETE FROM Sities WHERE Sities.id = " + QString::number(Sity));
		Sity = -1;
		Shop = -1;
		ui->Workers->setRowCount(0);
		ui->Connections->setRowCount(0);
		ui->Shops->setRowCount(0);
		reload_Sities();

	}  catch (const char* a) {
		My_Error error(a);
		error.exec();
	}
	catch(int k){
	}
}

void delete_db::on_Del_Client_clicked(){
	try {
		if (Client == -1) throw "Client not selected";

		if (!Ask_me("Это действие удалит ВСЕ магазины, подключения и работников этого клиента, продолжить?")) {
			throw 1;
		}

		QSqlQuery Query(m_db);
		Query.exec("SELECT DISTINCT t2.id FROM Shops as t2 "
							"JOIN Sities as t1 on t1.id = t2.Sity_id "
							"WHERE t2.Owner_id = " + QString::number(Client));

		while(Query.next()){
			delete_Shop(Query.value(0).toInt());
		}
		Query.exec("DELETE FROM Clients WHERE Clients.id = " + QString::number(Client));

		Client = -1;
		Sity = -1;
		Shop = -1;
		ui->Workers->setRowCount(0);
		ui->Connections->setRowCount(0);
		ui->Shops->setRowCount(0);
		reload_Clients();

	}  catch (const char* a) {
		My_Error error(a);
		error.exec();
	}
	catch(int k){
	}
}
