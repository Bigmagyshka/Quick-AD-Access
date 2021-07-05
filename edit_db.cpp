#include "edit_db.h"
#include "ui_edit_db.h"
#include "My_error.h"

#define FLAG_ON flag = true;
#define FLAG_OFF flag = false;

edit_DB::edit_DB(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::edit_DB)
{
	ui->setupUi(this);
	setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
	setModal(true);
}

edit_DB::edit_DB(QSqlDatabase &db) : QDialog(), ui(new Ui::edit_DB){
	ui->setupUi(this);
	setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
	setModal(true);
	this->db = db;

	if (db.open()){
		reload_Clients();
		reload_Sities();
	}else{
		My_Error error("DB is offline");
		error.exec();
	}

	ui->Choose_Client1->setColumnWidth(0,10);
	ui->Choose_Sity1->setColumnWidth(0,10);
	ui->Choose_Sity1->setColumnWidth(2,10);
	ui->Choose_Shop1->setColumnWidth(0,10);
	ui->DB_Clients->setColumnWidth(0,10);
	ui->DB_Sities->setColumnWidth(0,10);
	ui->Connect_Client->setColumnWidth(0,10);
	ui->Connect_Sity->setColumnWidth(0,10);
	ui->Connect_Shop->setColumnWidth(0,10);
	ui->Workers_Client->setColumnWidth(0,10);
	ui->Workers_Sity->setColumnWidth(0,10);
	ui->Workers_Shop->setColumnWidth(0,10);
	flag = true;
}

edit_DB::~edit_DB(){
	delete ui;
}


//Base functions
void edit_DB::reload_Clients(){
	QSqlQuery Query(db);
	QString Name, id;
	FLAG_OFF;
	ui->DB_Clients->setRowCount(0);
	ui->Choose_Client1->setRowCount(0);
	ui->Connect_Client->setRowCount(0);
	ui->Workers_Client->setRowCount(0);
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

		ui->Connect_Client->insertRow(ui->Connect_Client->rowCount());
		ui->Connect_Client->setItem(ui->Connect_Client->rowCount()-1, 0, new QTableWidgetItem(id));
		ui->Connect_Client->setItem(ui->Connect_Client->rowCount()-1, 1, new QTableWidgetItem(Name));

		ui->Workers_Client->insertRow(ui->Workers_Client->rowCount());
		ui->Workers_Client->setItem(ui->Workers_Client->rowCount()-1, 0, new QTableWidgetItem(id));
		ui->Workers_Client->setItem(ui->Workers_Client->rowCount()-1, 1, new QTableWidgetItem(Name));
	}
	FLAG_ON;
}

void edit_DB::reload_Sities(){
	QSqlQuery Query(db);
	QString Name, id;
	FLAG_OFF;
	ui->DB_Sities->setRowCount(0);
	ui->Choose_Sity1->setRowCount(0);
	Query.exec("SELECT * FROM Sities ORDER BY Sities.Name");
	while (Query.next()){
		id = Query.value(0).toString();
		Name = Query.value(1).toString();

		ui->DB_Sities->insertRow(ui->DB_Sities->rowCount());
		ui->DB_Sities->setItem(ui->DB_Sities->rowCount()-1, 0, new QTableWidgetItem(id));
		ui->DB_Sities->setItem(ui->DB_Sities->rowCount()-1, 1, new QTableWidgetItem(Name));

		ui->Choose_Sity1->insertRow(ui->Choose_Sity1->rowCount());
		ui->Choose_Sity1->setItem(ui->Choose_Sity1->rowCount()-1, 0, new QTableWidgetItem(id));
		ui->Choose_Sity1->setItem(ui->Choose_Sity1->rowCount()-1, 1, new QTableWidgetItem(Name));
	}
	FLAG_ON;
}

void edit_DB::reload_Shops_Choose(){
	QSqlQuery Query(db);
	QString Name, id;
	FLAG_OFF;
	ui->Choose_Shop1->setRowCount(0);

	Query.exec("SELECT t1.id, t1.Address "
						"FROM Shops as t1 "
						"JOIN Clients as t2 on t1.Owner_id = t2.id "
						"JOIN Sities as t3 on t1.Sity_id = t3.id "
						" Where t2.id = " + QString::number(chosen_client) +
						" AND t3.id = " + QString::number(chosen_sity) + " ORDER BY t1.Address");

	while (Query.next()){
		id = Query.value(0).toString();
		Name = Query.value(1).toString();

		ui->Choose_Shop1->insertRow(ui->Choose_Shop1->rowCount());
		ui->Choose_Shop1->setItem(ui->Choose_Shop1->rowCount()-1, 0, new QTableWidgetItem(id));
		ui->Choose_Shop1->setItem(ui->Choose_Shop1->rowCount()-1, 1, new QTableWidgetItem(Name));
	}
	FLAG_ON;
}

void edit_DB::reload_Connections(){
	QSqlQuery Query(db);
	QString Connection, Password, Name;
	bool Is_PC, Is_Angry;
	FLAG_OFF;
	Query.exec("SELECT * FROM Work_Places WHERE Work_Places.Shop_id = " + QString::number(connect_shop));

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
	FLAG_ON;
}

void edit_DB::reload_Workers(){
	QSqlQuery Query(db);
	QString Name, Number, Position;

	FLAG_OFF;
	Query.exec("SELECT * FROM Workers WHERE Workers.Shop_id = " + QString::number(worker_shop));

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
	FLAG_ON;
}


//Buttons
void edit_DB::on_Add_Client_clicked(){
	QString text = ui->textBrowser_2->toPlainText();
	if (!(text == "Введите имя" || text == "")){
		QSqlQuery Query(db);
		Query.exec("SELECT Clients.id FROM Clients ORDER BY Clients.id DESC limit 1 ");
		Query.next();
		Query.exec("INSERT INTO Clients VALUES (" + QString::number(Query.value(0).toInt() + 1) + ",\"" + text + "\")");
		reload_Workers();
	}else {
		My_Error error("Поле не изменено или пустое!");
		error.exec();
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
	}else {
		My_Error error("Поле не изменено или пустое!");
		error.exec();
	}
}

void edit_DB::on_Add_Shop_clicked(){
	try {
		if (chosen_sity == -1) throw "Choose Sity!";
		QString text = ui->Shop_Input->toPlainText();
		if (text == "Введите название" || text == "") throw "Name can't be empty";
		QSqlQuery Query(db);
		Query.exec("SELECT Shops.id FROM Shops ORDER BY Shops.id DESC limit 1 ");
		Query.next();
		Query.exec("INSERT INTO Shops VALUES (" + QString::number(Query.value(0).toInt() + 1) + ",\"" +
				   text + "\"," + QString::number(chosen_client) + "," +
				   QString::number(chosen_sity) + ")");
		reload_Shops_Choose();


	}  catch (const char* a) {
		My_Error error(a);
		error.exec();
	}

}

void edit_DB::on_Add_Connection_clicked(){
	try {
		if (connect_shop == -1) throw "No shop selected!";
		QString Name, Password, id;
		bool is_Angry, is_PC;
		Name = ui->Connect_Name->toPlainText();
		if(Name.isEmpty()) throw "Name can't be empty";
		Password = ui->Connect_Password->toPlainText();
		id = ui->Connect_id->toPlainText();
		if(id.toLong() < 100000000) throw "id can't be less than 100 000 000";
		is_Angry = ui->Connect_Angry->isChecked();
		is_PC = ui->Connect_PC->isChecked();

		QSqlQuery Query(db);
		Query.exec("INSERT INTO Work_Places VALUES (" + QString::number(connect_shop) + ", "
				+ QString::number(is_PC) + ", "
				+ "'" + id + "', '" + Password + "', '" + Name + "', "
				+ QString::number(is_Angry) + ")");
		reload_Connections();
	}  catch (const char* a) {
		My_Error error(a);
		error.exec();
	}
}

void edit_DB::on_Add_Worker_clicked(){
	try {
		if (worker_shop == -1) throw "No shop selected!";
		QString Name, Number, Position;

		Name = ui->Workers_Name->toPlainText();
		if(Name.isEmpty()) throw "Name can't be empty";
		Number = ui->Workers_Number->toPlainText();
		if(Number.isEmpty()) throw "Number can't be empty";
		Position = ui->Workers_Position->toPlainText();
		if(Position.isEmpty()) throw "Position can't be empty";

		QSqlQuery Query(db);
		Query.exec("INSERT INTO Workers VALUES (" + QString::number(worker_shop) + ", "
				+ "'" + Name + "', '" + Number + "', '" + Position + "')");
		reload_Workers();
	}  catch (const char* a) {
		My_Error error(a);
		error.exec();
	}
}



//"Add Client/Sity" Tab
void edit_DB::on_DB_Clients_cellChanged(int row, int column){
	if (column == 1 && flag){
		QSqlQuery Query(db);
		QString Name, id;

		QTableWidgetItem *item = ui->DB_Clients->item(row,0);
		if (NULL != item) id = item->text();
		item =  ui->DB_Clients->item(row,1);
		if (NULL != item) Name = item->text();

		Query.exec("UPDATE Clients SET Name='" + Name + "' WHERE id=" + id + ";");

		reload_Clients();

	}
}

void edit_DB::on_DB_Sities_cellChanged(int row, int column){
	if (column == 1 && flag){
		QSqlQuery Query(db);
		QString Name, id;

		QTableWidgetItem *item = ui->DB_Sities->item(row,0);
		if (NULL != item) id = item->text();
		item =  ui->DB_Sities->item(row,1);
		if (NULL != item) Name = item->text();

		Query.exec("UPDATE Sities SET Name='" + Name + "' WHERE id=" + id + ";");

		reload_Sities();
	}
}


//"Add Shop" Tab
void edit_DB::on_Choose_Shop1_cellChanged(int row, int column){
	if (column == 1 && flag){
		QSqlQuery Query(db);
		QString Address, id;

		QTableWidgetItem *item = ui->Choose_Shop1->item(row,0);
		if (NULL != item) id = item->text();
		item =  ui->Choose_Shop1->item(row,1);
		if (NULL != item) Address = item->text();

		Query.exec("UPDATE Shops SET Address='" + Address + "' WHERE id=" + id + ";");

		reload_Shops_Choose();
	}
}

void edit_DB::on_Choose_Client1_cellClicked(int row){
	QSqlQuery Query(db),count(db);
	QString Name, id, id_sity;

	QTableWidgetItem *item = ui->Choose_Client1->item(row,0);
	if (NULL != item) id = item->text();
	chosen_client = id.toInt();
	chosen_sity = -1;

	Query.exec("SELECT DISTINCT t1.id FROM Shops as t2 "
						"JOIN Sities as t1 on t1.id = t2.Sity_id "
						"WHERE t2.Owner_id = " + id + " ORDER BY t1.Name");
	bool flag = true;

	for (int i = 0; i < ui->Choose_Sity1->rowCount(); i++) {
		ui->Choose_Sity1->setItem(i,2, new QTableWidgetItem(0));
	}

	if (!Query.next()) flag = false;

	for (int i = 0; (i < ui->Choose_Sity1->rowCount()) && flag; i++){
		item = ui->Choose_Sity1->item(i,0);
		id_sity = item->text();

		if (id_sity == Query.value(0).toString()){
			count.exec("SELECT count (t1.Address) "
								"FROM Shops as t1 "
								"JOIN Clients as t2 on t1.Owner_id = t2.id "
								"JOIN Sities as t3 on t1.Sity_id = t3.id "
								" Where t2.id = " + id +
								" AND t3.id = " + id_sity);
			count.next();
			ui->Choose_Sity1->setItem(i,2, new QTableWidgetItem(count.value(0).toString()));
			if (!Query.next()) flag = false;
		}
	}
}

void edit_DB::on_Choose_Sity1_cellClicked(int row){
	QString id;
	QTableWidgetItem *item = ui->Choose_Sity1->item(row,0);
	if (NULL != item) id = item->text();
	chosen_sity = id.toInt();

	reload_Shops_Choose();
}


//"Add Connection" Tab
void edit_DB::on_Connect_Client_cellClicked(int row){
	QSqlQuery Query(db);
	QString Name, id;

	QTableWidgetItem *item = ui->Connect_Client->item(row,0);
	if (NULL != item) id = item->text();
	connect_client = id.toInt();
	connect_shop = -1;
	connect_sity = -1;

	Query.exec("SELECT DISTINCT t1.id, t1.Name FROM Shops as t2 "
						"JOIN Sities as t1 on t1.id = t2.Sity_id "
						"WHERE t2.Owner_id = " + id + " ORDER BY t1.Name");


	ui->Connect_Sity->setRowCount(0);
	ui->Connect_Shop->setRowCount(0);
	ui->Connections->setRowCount(0);

	while (Query.next()){
		id = Query.value(0).toString();
		Name = Query.value(1).toString();

		ui->Connect_Sity->insertRow(ui->Connect_Sity->rowCount());
		ui->Connect_Sity->setItem(ui->Connect_Sity->rowCount()-1, 0, new QTableWidgetItem(id));
		ui->Connect_Sity->setItem(ui->Connect_Sity->rowCount()-1, 1, new QTableWidgetItem(Name));
	}
}

void edit_DB::on_Connect_Sity_cellClicked(int row){
	QSqlQuery Query(db);
	QString Name, id;

	QTableWidgetItem *item = ui->Connect_Sity->item(row,0);
	if (NULL != item) id = item->text();
	connect_sity = id.toInt();
	connect_shop = -1;

	ui->Connect_Shop->setRowCount(0);
	ui->Connections->setRowCount(0);

	Query.exec("SELECT t1.id, t1.Address "
						"FROM Shops as t1 "
						"JOIN Clients as t2 on t1.Owner_id = t2.id "
						"JOIN Sities as t3 on t1.Sity_id = t3.id "
						" Where t2.id = " + QString::number(connect_client) +
						" AND t3.id = " + QString::number(connect_sity) + " ORDER BY t1.Address");

	while (Query.next()){
		id = Query.value(0).toString();
		Name = Query.value(1).toString();

		ui->Connect_Shop->insertRow(ui->Connect_Shop->rowCount());
		ui->Connect_Shop->setItem(ui->Connect_Shop->rowCount()-1, 0, new QTableWidgetItem(id));
		ui->Connect_Shop->setItem(ui->Connect_Shop->rowCount()-1, 1, new QTableWidgetItem(Name));
	}
}

void edit_DB::on_Connect_Shop_cellClicked(int row){

	QTableWidgetItem *item = ui->Connect_Shop->item(row,0);
	if (NULL != item) connect_shop = item->text().toInt();

	reload_Connections();
}

void edit_DB::on_Connections_cellChanged(int row, int column){
	if (flag) {
		QSqlQuery Query(db);
		QString Connection, Changed;

		QTableWidgetItem *item = ui->Connections->item(row,1);
		Connection = item->text();


		switch (column) {
			case 0:
				item = ui->Connections->item(row,0);
				Changed = item->text();
				Query.exec("UPDATE Work_Places SET Is_PC= " + Changed + " WHERE Connection= '" + Connection + "';");
			break;

			case 1:
				item = ui->Connections->item(row,3);
				Changed = item->text();
				Query.exec("UPDATE Work_Places SET Connection= '" + Connection + "' WHERE Name= '" + Changed + "' AND Shop_id = "+ QString::number(connect_shop) +";");
			break;

			case 2:
				item = ui->Connections->item(row,2);
				Changed = item->text();
				Query.exec("UPDATE Work_Places SET Password='" + Changed + "' WHERE Connection= '" + Connection + "';");
			break;

			case 3:
				item = ui->Connections->item(row,3);
				Changed = item->text();
				Query.exec("UPDATE Work_Places SET Name='" + Changed + "' WHERE Connection= '" + Connection + "';");
			break;

			case 4:
				item = ui->Connections->item(row,4);
				Changed = item->text();
				Query.exec("UPDATE Work_Places SET Is_Angry= " + Changed + " WHERE Connection= '" + Connection + "';");
		}

		reload_Connections();
	}
}



//"Add Worker" Tab
void edit_DB::on_Workers_Client_cellClicked(int row){
	QSqlQuery Query(db);
	QString Name, id;

	QTableWidgetItem *item = ui->Workers_Client->item(row,0);
	if (NULL != item) id = item->text();
	worker_client = id.toInt();
	worker_shop = -1;
	worker_sity = -1;

	Query.exec("SELECT DISTINCT t1.id, t1.Name FROM Shops as t2 "
						"JOIN Sities as t1 on t1.id = t2.Sity_id "
						"WHERE t2.Owner_id = " + id + " ORDER BY t1.Name");


	ui->Workers_Sity->setRowCount(0);
	ui->Workers_Shop->setRowCount(0);
	ui->Workers->setRowCount(0);

	while (Query.next()){
		id = Query.value(0).toString();
		Name = Query.value(1).toString();

		ui->Workers_Sity->insertRow(ui->Workers_Sity->rowCount());
		ui->Workers_Sity->setItem(ui->Workers_Sity->rowCount()-1, 0, new QTableWidgetItem(id));
		ui->Workers_Sity->setItem(ui->Workers_Sity->rowCount()-1, 1, new QTableWidgetItem(Name));
	}
}

void edit_DB::on_Workers_Sity_cellClicked(int row){
	QSqlQuery Query(db);
	QString Name, id;

	QTableWidgetItem *item = ui->Workers_Sity->item(row,0);
	if (NULL != item) id = item->text();
	worker_sity = id.toInt();
	worker_shop = -1;

	ui->Workers_Shop->setRowCount(0);
	ui->Workers->setRowCount(0);

	Query.exec("SELECT t1.id, t1.Address "
						"FROM Shops as t1 "
						"JOIN Clients as t2 on t1.Owner_id = t2.id "
						"JOIN Sities as t3 on t1.Sity_id = t3.id "
						" Where t2.id = " + QString::number(worker_client) +
						" AND t3.id = " + QString::number(worker_sity) + " ORDER BY t1.Address");

	while (Query.next()){
		id = Query.value(0).toString();
		Name = Query.value(1).toString();

		ui->Workers_Shop->insertRow(ui->Workers_Shop->rowCount());
		ui->Workers_Shop->setItem(ui->Workers_Shop->rowCount()-1, 0, new QTableWidgetItem(id));
		ui->Workers_Shop->setItem(ui->Workers_Shop->rowCount()-1, 1, new QTableWidgetItem(Name));
	}

}

void edit_DB::on_Workers_Shop_cellClicked(int row){
	QTableWidgetItem *item = ui->Workers_Shop->item(row,0);
	if (NULL != item) worker_shop = item->text().toInt();

	reload_Workers();
}

void edit_DB::on_Workers_cellChanged(int row, int column){
	if (flag) {
		QSqlQuery Query(db);
		QString Name, Number, Position;

		QTableWidgetItem *item = ui->Workers->item(row,0);
		Name = item->text();
		item = ui->Workers->item(row,1);
		Number = item->text();
		item = ui->Workers->item(row,2);
		Position = item->text();

		switch (column) {
			case 0:
				Query.exec("UPDATE Workers SET Name= '" + Name + "' WHERE Shop_id= " + QString::number(worker_shop) + " AND Number = '" + Number + "';");
			break;

			case 1:
				Query.exec("UPDATE Workers SET Number= '" + Number + "' WHERE Shop_id= " + QString::number(worker_shop) + " AND Name = '" + Name + ";");
			break;

			case 2:
				Query.exec("UPDATE Workers SET Position='" + Position + "' WHERE Shop_id= " + QString::number(worker_shop) + " AND Number = '" + Number + ";");
			}

		reload_Workers();
	}
}
