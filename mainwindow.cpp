#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QSqlDriver>
#include <thread>

#include "My_error.h"
#include "ask.h"
#include "edit_db.h"
#include "delete_db.h"
#include "Containers/Client.h"
#include "Containers/Sity.h"
#include "Containers/Card.h"
#include "Containers/ADButton.h"

#ifndef __linux__
#include "windows.h"
#endif

void Run(QString path);
void Ask(QString path);

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow){
	ui->setupUi(this);
}

MainWindow::MainWindow()
	: QMainWindow()
	, ui(new Ui::MainWindow){
	ui->setupUi(this);
	db = QSqlDatabase::addDatabase("QSQLITE");
}

MainWindow::~MainWindow(){
	delete ui;
	delete[] Clients;
}

//Base Functions
void MainWindow::Reload_DB(){
	int client = ui->tabWidget->currentIndex(), sity = Clients[client].get_index();

	Client *OLD = Clients;
	while (ui->tabWidget->count())
		ui->tabWidget->removeTab(0);


	read_DB();

	if(client <= ui->tabWidget->count()){
		ui->tabWidget->setCurrentIndex(client);
		Clients[client].set_index(sity);
	}

	delete[] OLD;
}


// Add main data from DB
void addButtons(int shop_id, QSqlDatabase db, Card &cur_card){
	QSqlQuery Query(db);

	Query.exec("SELECT * FROM Work_Places WHERE Work_Places.Shop_id = " + QString::number(shop_id) + " ORDER BY Work_Places.Is_PC DESC");

	while (Query.next()){
			cur_card.add_button(Query.value(2).toLongLong(),Query.value(3).toString(),Query.value(4).toString(), Query.value(5).toBool());
	}
}

void addWorkers(int shop_id, QSqlDatabase db, Card &cur_card){
	QSqlQuery Query(db);

	Query.exec("SELECT * FROM Workers WHERE Workers.Shop_id = " + QString::number(shop_id));

	while (Query.next())
		cur_card.add_Worker(Query.value(1).toString(),Query.value(3).toString(),Query.value(2).toString());
}

Card* Add_Cards(QSqlDatabase db, int &cd, int id_client, int id_sity){
	QSqlQuery Cards_Query(db);

	Cards_Query.exec("SELECT count (t1.Address) "
						"FROM Shops as t1 "
						"JOIN Clients as t2 on t1.Owner_id = t2.id "
						"JOIN Sities as t3 on t1.Sity_id = t3.id "
						" Where t2.id = " + QString::number(id_client) +
						" AND t3.id = " + QString::number(id_sity));
	Cards_Query.next();
	cd = Cards_Query.value(0).toInt();
	if (cd == 0) return nullptr;

	Card *Cards = new Card [cd];

	Cards_Query.exec("SELECT t1.id, t1.Address "
						"FROM Shops as t1 "
						"JOIN Clients as t2 on t1.Owner_id = t2.id "
						"JOIN Sities as t3 on t1.Sity_id = t3.id "
						" Where t2.id = " + QString::number(id_client) +
						" AND t3.id = " + QString::number(id_sity) + " ORDER BY t1.Address");

	int step = 0;
	while (Cards_Query.next()){
		Cards[step].set_id(Cards_Query.value(0).toInt());
		Cards[step].set_name(Cards_Query.value(1).toString());
		addButtons(Cards[step].get_id(), db, Cards[step]);
		addWorkers(Cards[step].get_id(), db, Cards[step]);
		step++;
	}

	return Cards;
}

Sity* Add_Sities(QSqlDatabase db, int &st, int id, Client *cl){
	QSqlQuery Sities_Query(db);

	Sities_Query.exec("SELECT count (DISTINCT Sities.Name) FROM Shops "
						"JOIN Sities on Sities.id = Shops.Sity_id "
						"WHERE Shops.Owner_id = " + QString::number(id));
	Sities_Query.next();
	st = Sities_Query.value(0).toInt();
	if (st == 0) return nullptr;

	Sity *Sities = new Sity [st];
	for (int i = 0; i < st; i++)
		Sities[i].setParent(cl);

	Sities_Query.exec("SELECT DISTINCT t1.id, t1.Name FROM Shops as t2 "
						"JOIN Sities as t1 on t1.id = t2.Sity_id "
						"WHERE t2.Owner_id = " + QString::number(id) + " ORDER BY t1.Name");

	int step = 0, cd;
	while (Sities_Query.next()){
		Sities[step].set_id(Sities_Query.value(0).toInt());
		Sities[step].set_name(Sities_Query.value(1).toString());
		Sities[step].cards = Add_Cards(db, cd, id, Sities[step].get_id());
		Sities[step].set_count(cd);
		for (int z = 0; z < Sities[step].get_count(); z++)
			Sities[step].addCard(z);
		step++;
	}

	return Sities;
}

Client* Add_Clients(QSqlDatabase db, int &cl){
	QSqlQuery Clients_Query(db);

	Clients_Query.exec("SELECT COUNT() FROM Clients");
	Clients_Query.next();
	cl = Clients_Query.value(0).toInt();	
	if (cl == 0) return nullptr;

	Client *Clients = new Client [cl];

	Clients_Query.exec("SELECT * FROM Clients ORDER BY Clients.Name");

	int step = 0, st;
	while (Clients_Query.next()){
		Clients[step].set_id(Clients_Query.value(0).toInt());
		Clients[step].set_name(Clients_Query.value(1).toString());
		Clients[step].sities = Add_Sities(db,st,Clients[step].get_id(), &Clients[step]);
		Clients[step].set_count(st);
		for (int z = 0; z < Clients[step].get_count(); z++)
			Clients[step].addTab(z);
		step++;
	}
	return Clients;
}

bool MainWindow::read_DB(){
	db.setDatabaseName("./Sourse/main_db.db");

	if (!db.open()) {
		My_Error error("DB is offline");
		error.exec();
		return 0;
	}

	int cl;
	Clients = Add_Clients(db, cl);
	for (int i = 0; i < cl; i++)
		ui->tabWidget->addTab(&Clients[i],Clients[i].get_name());

	for (int i = 0; i < cl; i++){
		for (int i2 = 0; i2 < Clients[i].get_count(); i2++){
			for (int i3 = 0; i3 < Clients[i].sities[i2].get_count(); i3++){
				for (int i4 = 0; i4 < Clients[i].sities[i2].cards[i3].get_count(); i4++){
					connect(&(Clients[i].sities[i2].cards[i3].buttons[i4]),SIGNAL(clicked()), this, SLOT(open_connect()));
				}
			}
		}
	}

	return 1;
}


//Work with Connections
void kill(){
	std::this_thread::sleep_for(std::chrono::milliseconds(3000));
	system("taskkill /IM cmd.exe");
}

void Run(QString path){
	std::thread thr1(system,path.toLocal8Bit().data()), thr2(kill);
	thr1.detach();
	thr2.detach();
}

void Ask(QString path){
	bool k;
	ask Ask(k,"Управляющий требует, чтобы перед подключением к кассе ему позвонили !!!");
	Ask.exec();
	if (k) Run(path);
}

void MainWindow::open_connect(){
	ADButton *button = (ADButton*) sender();
	if (button->get_angry())
		Ask ("echo " + button->get_pas() + " | " + ".\\AnyDesk.exe " + QString::number(button->get_id()) + + " --with-password");
	else
		Run ("echo " + button->get_pas() + " | " + ".\\AnyDesk.exe " + QString::number(button->get_id()) + + " --with-password");
}


//Menu Buttons
void MainWindow::on_Menu_1_triggered(){
	Reload_DB();
}

void MainWindow::on_Edit_DB_triggered(){
	edit_DB Edit_DB(db);
	Edit_DB.exec();
	Reload_DB();
}

void MainWindow::on_Delete_From_DB_triggered(){
	delete_db Delete_DB(db);
	Delete_DB.exec();
	Reload_DB();
}

