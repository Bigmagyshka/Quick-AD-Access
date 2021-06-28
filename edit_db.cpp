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
		QSqlQuery Query(db);

		QString id;
		QString Name;

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

		Query.exec("SELECT * FROM Sities ORDER BY Sities.Name");
		while (Query.next()){
			id = Query.value(0).toString();
			Name = Query.value(1).toString();

			ui->DB_Sities->insertRow(ui->DB_Sities->rowCount());
			ui->DB_Sities->setItem(ui->DB_Sities->rowCount()-1, 0, new QTableWidgetItem(id));
			ui->DB_Sities->setItem(ui->DB_Sities->rowCount()-1, 1, new QTableWidgetItem(Name));
		}
	}

	flag = true;
}

edit_DB::~edit_DB()
{
	delete ui;
}

void edit_DB::on_pushButton_5_clicked(){
	QString text = ui->textBrowser_2->toPlainText();
	if (!(text == "Введите имя" || text == "")){
		QSqlQuery Query(db);
		Query.exec("SELECT Clients.id FROM Clients ORDER BY Clients.id DESC limit 1 ");
		Query.next();
		Query.exec("INSERT INTO Clients VALUES (" + QString::number(Query.value(0).toInt() + 1) + ",\"" + text + "\")");


		QString id;
		QString Name;
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
}

void edit_DB::on_pushButton_4_clicked(){
	QString text = ui->textBrowser_2->toPlainText();
	if (!(text == "Введите имя" || text == "")){
		QSqlQuery Query(db);
		Query.exec("SELECT Sities.id FROM Sities ORDER BY Sities.id DESC limit 1 ");
		Query.next();
		Query.exec("INSERT INTO Sities VALUES (" + QString::number(Query.value(0).toInt() + 1) + ",\"" + text + "\")");


		QString id;
		QString Name;
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
		flag = true;
	}
}
