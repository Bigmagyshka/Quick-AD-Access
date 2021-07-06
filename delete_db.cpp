#include "delete_db.h"
#include "ui_delete_db.h"
#include "My_error.h"

delete_db::delete_db(QWidget *parent) : QDialog(parent), ui(new Ui::delete_db){
	ui->setupUi(this);
}

delete_db::delete_db(QSqlDatabase &db) : QDialog(), ui(new Ui::delete_db){

	ui->setupUi(this);
	setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
	setModal(true);
	this->db = db;
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
}

void delete_db::reload_Clients(){
	QSqlQuery Query(db);
	QString Name, id;

	ui->Clients->setRowCount(0);

	Query.exec("SELECT * FROM Clients ORDER BY Clients.Name");
	while (Query.next()){
		id = Query.value(0).toString();
		Name = Query.value(1).toString();

		ui->Clients->insertRow(ui->Clients->rowCount());
		ui->Clients->setItem(ui->Clients->rowCount()-1, 0, new QTableWidgetItem(id));
		ui->Clients->setItem(ui->Clients->rowCount()-1, 1, new QTableWidgetItem(Name));

	}
}

void delete_db::reload_Sities(){
	QSqlQuery Query(db);
	QString Name, id;
	ui->Sities->setRowCount(0);
	Query.exec("SELECT * FROM Sities ORDER BY Sities.Name");
	while (Query.next()){
		id = Query.value(0).toString();
		Name = Query.value(1).toString();

		ui->Sities->insertRow(ui->Sities->rowCount());
		ui->Sities->setItem(ui->Sities->rowCount()-1, 0, new QTableWidgetItem(id));
		ui->Sities->setItem(ui->Sities->rowCount()-1, 1, new QTableWidgetItem(Name));
	}
}

void delete_db::reload_Shops(){
	QString id, Name;
	QSqlQuery Query(db);

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
		id = Query.value(0).toString();
		Name = Query.value(1).toString();

		ui->Shops->insertRow(ui->Shops->rowCount());
		ui->Shops->setItem(ui->Shops->rowCount()-1, 0, new QTableWidgetItem(id));
		ui->Shops->setItem(ui->Shops->rowCount()-1, 1, new QTableWidgetItem(Name));
	}
}

void delete_db::reload_Connections(){
	QSqlQuery Query(db);
	QString Connection, Password, Name;
	bool Is_PC, Is_Angry;

	Query.exec("SELECT * FROM Work_Places WHERE Work_Places.Shop_id = " + QString::number(Shop));

	ui->Connections->setRowCount(0);
	while (Query.next()){
		Is_PC = Query.value(1).toBool();
		Connection = Query.value(2).toString();
		Password = Query.value(3).toString();
		Name = Query.value(4).toString();
		Is_Angry = Query.value(5).toBool();

		ui->Connections->insertRow(ui->Connections->rowCount());
		ui->Connections->setItem(ui->Connections->rowCount()-1, 0, new QTableWidgetItem(Is_PC?"1":"0"));
		ui->Connections->setItem(ui->Connections->rowCount()-1, 1, new QTableWidgetItem(Connection));
		ui->Connections->setItem(ui->Connections->rowCount()-1, 2, new QTableWidgetItem(Password));
		ui->Connections->setItem(ui->Connections->rowCount()-1, 3, new QTableWidgetItem(Name));
		ui->Connections->setItem(ui->Connections->rowCount()-1, 4, new QTableWidgetItem(Is_Angry?"1":"0"));
	}
}

void delete_db::reload_Workers(){
	QSqlQuery Query(db);
	QString Name, Number, Position;

	Query.exec("SELECT * FROM Workers WHERE Workers.Shop_id = " + QString::number(Shop));
	ui->Workers->setRowCount(0);
	while (Query.next()){
		Name = Query.value(1).toString();
		Number = Query.value(2).toString();
		Position = Query.value(3).toString();

		ui->Workers->insertRow(ui->Workers->rowCount());
		ui->Workers->setItem(ui->Workers->rowCount()-1, 0, new QTableWidgetItem(Name));
		ui->Workers->setItem(ui->Workers->rowCount()-1, 1, new QTableWidgetItem(Number));
		ui->Workers->setItem(ui->Workers->rowCount()-1, 2, new QTableWidgetItem(Position));
	}
}

void delete_db::delete_Shop(int a){
	QSqlQuery Query(db);
	Query.exec("DELETE FROM Workers WHERE Workers.Shop_id = " + QString::number(a));
	Query.exec("DELETE FROM Work_Places WHERE Work_Places.Shop_id = " + QString::number(a));
	Query.exec("DELETE FROM Shops WHERE Shops.id = " + QString::number(a));
}

void delete_db::on_Clients_cellClicked(int row){

	QSqlQuery Query(db),count(db);
	QString Name, id, id_sity;

	QTableWidgetItem *item = ui->Clients->item(row,0);
	if (NULL != item) id = item->text();
	Client = id.toInt();
	Sity = -1;
	Shop = -1;
	Connection = "";
	Number = "";

	ui->Shops->setRowCount(0);
	ui->Connections->setRowCount(0);
	ui->Workers->setRowCount(0);

	Query.exec("SELECT DISTINCT t1.id FROM Shops as t2 "
						"JOIN Sities as t1 on t1.id = t2.Sity_id "
						"WHERE t2.Owner_id = " + id + " ORDER BY t1.Name");

	for (int i = 0; i < ui->Sities->rowCount(); i++) {
		ui->Sities->setItem(i,2, new QTableWidgetItem(0));
	}

	if (!Query.next()) return;

	for (int i = 0; (i < ui->Sities->rowCount()); i++){
		item = ui->Sities->item(i,0);
		id_sity = item->text();

		if (id_sity == Query.value(0).toString()){
			count.exec("SELECT count (t1.Address) "
								"FROM Shops as t1 "
								"JOIN Clients as t2 on t1.Owner_id = t2.id "
								"JOIN Sities as t3 on t1.Sity_id = t3.id "
								" Where t2.id = " + id +
								" AND t3.id = " + id_sity);
			count.next();
			ui->Sities->setItem(i,2, new QTableWidgetItem(count.value(0).toString()));
			if (!Query.next()) return;
		}
	}
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

void delete_db::on_Del_Connection_clicked(){
	try {
		if (Connection.isEmpty()) throw "Connection not selected";
		QSqlQuery Query(db);
		Query.exec("DELETE FROM Work_Places WHERE Work_Places.Connection = '" + Connection + "'");
		reload_Connections();
	}  catch (const char* a) {
		My_Error error(a);
		error.exec();
	}
}

void delete_db::on_Del_Worker_clicked(){
	try {
		if (Number.isEmpty()) throw "Worker not selected";
		QSqlQuery Query(db);
		Query.exec("DELETE FROM Workers WHERE Workers.Number = '" + Number + "'");
		reload_Workers();
	}  catch (const char* a) {
		My_Error error(a);
		error.exec();
	}
}

void delete_db::on_Del_Shop_clicked(){
	try {
		if (Shop == -1) throw "Shop not selected";
		delete_Shop(Shop);
		Shop = -1;
		ui->Workers->setRowCount(0);
		ui->Connections->setRowCount(0);
		reload_Shops();
	}  catch (const char* a) {
		My_Error error(a);
		error.exec();
	}
}

void delete_db::on_Del_Sity_clicked(){
	try {
		if (Sity == -1) throw "Sity not selected";
		QSqlQuery Query(db);
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
}

void delete_db::on_Del_Client_clicked(){
	try {
		if (Client == -1) throw "Client not selected";
		QSqlQuery Query(db);
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
}
