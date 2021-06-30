#include "edit_db.h"
#include "ui_edit_db.h"

edit_DB::edit_DB(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::edit_DB)
{
	ui->setupUi(this);
	setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
	setModal(true);
}

edit_DB::edit_DB(QSqlDatabase &db) :
	QDialog(),
	ui(new Ui::edit_DB)
{
	ui->setupUi(this);
	setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
	setModal(true);
	this->db = db;

	if (db.open()){
		reload_Clients();
		reload_Sities();
	}

	flag = true;
}

edit_DB::~edit_DB()
{
	delete ui;
}

void edit_DB::reload_Clients(){
	QSqlQuery Query(db);
	QString Name, id;

	ui->DB_Clients->setRowCount(0);
	ui->Choose_Client1->setRowCount(0);
	Query.exec("SELECT * FROM Clients ORDER BY Clients.Name");
	while (Query.next()){
		id = Query.value(0).toString();
		Name = Query.value(1).toString();

		ui->Choose_Client1->insertRow(ui->Choose_Client1->rowCount());
		ui->Choose_Client1->setItem(ui->Choose_Client1->rowCount()-1, 0, new QTableWidgetItem(id));
		ui->Choose_Client1->setItem(ui->Choose_Client1->rowCount()-1, 1, new QTableWidgetItem(Name));

		ui->DB_Clients->insertRow(ui->DB_Clients->rowCount());
		ui->DB_Clients->setItem(ui->DB_Clients->rowCount()-1, 0, new QTableWidgetItem(id));
		ui->DB_Clients->setItem(ui->DB_Clients->rowCount()-1, 1, new QTableWidgetItem(Name));
	}
}

void edit_DB::reload_Sities(){
	QSqlQuery Query(db);
	QString Name, id;

	ui->DB_Sities->setRowCount(0);
	Query.exec("SELECT * FROM Sities ORDER BY Sities.Name");
	while (Query.next()){
		id = Query.value(0).toString();
		Name = Query.value(1).toString();

		ui->DB_Sities->insertRow(ui->DB_Sities->rowCount());
		ui->DB_Sities->setItem(ui->DB_Sities->rowCount()-1, 0, new QTableWidgetItem(id));
		ui->DB_Sities->setItem(ui->DB_Sities->rowCount()-1, 1, new QTableWidgetItem(Name));
	}
}

void edit_DB::on_Add_Client_clicked(){
	QString text = ui->textBrowser_2->toPlainText();
	if (!(text == "Введите имя" || text == "")){
		QSqlQuery Query(db);
		Query.exec("SELECT Clients.id FROM Clients ORDER BY Clients.id DESC limit 1 ");
		Query.next();
		Query.exec("INSERT INTO Clients VALUES (" + QString::number(Query.value(0).toInt() + 1) + ",\"" + text + "\")");
		reload_Clients();
	}
}

void edit_DB::on_Add_Sity_clicked(){
	QString text = ui->textBrowser_2->toPlainText();
	if (!(text == "Введите имя" || text == "")){
		QSqlQuery Query(db);
		Query.exec("SELECT Sities.id FROM Sities ORDER BY Sities.id DESC limit 1 ");
		Query.next();
		Query.exec("INSERT INTO Sities VALUES (" + QString::number(Query.value(0).toInt() + 1) + ",\"" + text + "\")");
		reload_Sities();
	}
}

void edit_DB::on_DB_Clients_cellChanged(int row, int column){
	if (column == 1 && flag){
		flag = false;

		QSqlQuery Query(db);
		QString Name, id;

		QTableWidgetItem *item = ui->DB_Clients->item(row,0);
		if (NULL != item) id = item->text();
		item =  ui->DB_Clients->item(row,1);
		if (NULL != item) Name = item->text();

		Query.exec("UPDATE Clients SET Name='" + Name + "' WHERE id=" + id + ";");

		reload_Clients();

		flag = true;
	}
}

void edit_DB::on_DB_Sities_cellChanged(int row, int column){
	if (column == 1 && flag){
		flag = false;

		QSqlQuery Query(db);
		QString Name, id;

		QTableWidgetItem *item = ui->DB_Sities->item(row,0);
		if (NULL != item) id = item->text();
		item =  ui->DB_Sities->item(row,1);
		if (NULL != item) Name = item->text();

		Query.exec("UPDATE Sities SET Name='" + Name + "' WHERE id=" + id + ";");

		reload_Sities();

		flag = true;
	}
}

void edit_DB::on_Choose_Client1_cellClicked(int row, int column){
	QSqlQuery Query(db);
	QString Name, id;

	chosen_client = row;

	QTableWidgetItem *item = ui->Choose_Client1->item(chosen_client,0);
	if (NULL != item) id = item->text();

	ui->Choose_Sity1->setRowCount(0);
	Query.exec("SELECT DISTINCT t1.id, t1.Name FROM Shops as t2 "
						"JOIN Sities as t1 on t1.id = t2.Sity_id "
						"WHERE t2.Owner_id = " + id + " ORDER BY t1.Name");

	while (Query.next()){
		id = Query.value(0).toString();
		Name = Query.value(1).toString();

		ui->Choose_Sity1->insertRow(ui->Choose_Sity1->rowCount());
		ui->Choose_Sity1->setItem(ui->Choose_Sity1->rowCount()-1, 0, new QTableWidgetItem(id));
		ui->Choose_Sity1->setItem(ui->Choose_Sity1->rowCount()-1, 1, new QTableWidgetItem(Name));
	}

}

void edit_DB::on_Choose_Sity1_cellClicked(int row, int column){
	QSqlQuery Query(db);
	QString Name, id, id_client;

	chosen_sity = row;

	QTableWidgetItem *item = ui->Choose_Client1->item(chosen_client,0);
	if (NULL != item) id_client = item->text();
	item =  ui->Choose_Sity1->item(chosen_sity,0);
	if (NULL != item) id = item->text();

	ui->Choose_Shop1->setRowCount(0);
	Query.exec("SELECT t1.id, t1.Address "
						"FROM Shops as t1 "
						"JOIN Clients as t2 on t1.Owner_id = t2.id "
						"JOIN Sities as t3 on t1.Sity_id = t3.id "
						" Where t2.id = " + id_client +
						" AND t3.id = " + id + " ORDER BY t1.Address");

	while (Query.next()){
		id = Query.value(0).toString();
		Name = Query.value(1).toString();

		ui->Choose_Shop1->insertRow(ui->Choose_Shop1->rowCount());
		ui->Choose_Shop1->setItem(ui->Choose_Shop1->rowCount()-1, 0, new QTableWidgetItem(id));
		ui->Choose_Shop1->setItem(ui->Choose_Shop1->rowCount()-1, 1, new QTableWidgetItem(Name));
	}
}
