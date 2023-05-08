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
#include "Containers/ClientButton.h"
#include "Containers/Sity.h"
#include "Containers/Card.h"
#include "Containers/ADButton.h"

#ifndef __linux__
#include "windows.h"
#endif

void Run(QString path);
void Ask(QString path);

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
	ui->setupUi(this);
	m_db = QSqlDatabase::addDatabase("QSQLITE");
}

//Base Functions
void MainWindow::Reload_DB(){
	for(auto item : m_vecClientButtons)
		item->deleteLater();
	m_pLastSelectedButton = nullptr;

	read_DB();
}

void MainWindow::SetSities()
{
	auto pSender = dynamic_cast<ClientButton *>(sender());
	if(!pSender)
		return;

	if(m_pLastSelectedButton)
		m_pLastSelectedButton->setEnabled(true);
	m_pLastSelectedButton = pSender;

	pSender->setEnabled(false);

	ui->tabWidget->clear();
	m_vecCurSities = GetSities(pSender->GetID());

	for(auto pSity : m_vecCurSities)
		ui->tabWidget->addTab(pSity, pSity->GetName());
}


// Add main data from DB
void MainWindow::addButtons(int shop_id, Card &cur_card){
	QSqlQuery Query(m_db);

	Query.exec("SELECT * FROM Work_Places WHERE Work_Places.Shop_id = " + QString::number(shop_id) + " ORDER BY Work_Places.Is_PC DESC");

	while(Query.next())
	{
		auto nConnectionID {Query.value(2).toLongLong()};
		auto sPassword {Query.value(3).toString()};
		auto sName {Query.value(4).toString()};
		auto bIsAngry{Query.value(5).toBool()};

		if(!cur_card.add_button(nConnectionID, sPassword, sName, bIsAngry))
			break;
	}
}

void MainWindow::addWorkers(int shop_id, Card &cur_card){
	QSqlQuery Query(m_db);

	Query.exec("SELECT * FROM Workers WHERE Workers.Shop_id = " + QString::number(shop_id));

	while (Query.next())
	{
		auto sName {Query.value(1).toString()};
		auto sPosition {Query.value(3).toString()};
		auto sNumber {Query.value(2).toString()};

		if(!cur_card.add_Worker(sName, sPosition, sNumber))
			break;
	}
}

QVector<Card *> MainWindow::Add_Cards(int id_client, int id_sity)
{
	QSqlQuery Cards_Query(m_db);
	QVector<Card *> vecCards;

	Cards_Query.exec("SELECT t1.id, t1.Address "
						"FROM Shops as t1 "
						"JOIN Clients as t2 on t1.Owner_id = t2.id "
						"JOIN Sities as t3 on t1.Sity_id = t3.id "
						" Where t2.id = " + QString::number(id_client) +
						" AND t3.id = " + QString::number(id_sity) + " ORDER BY t1.Address");

	while (Cards_Query.next()){
		auto nShopID = Cards_Query.value(0).toInt();
		auto sShopName = Cards_Query.value(1).toString();

		auto pCard = new Card(nullptr, nShopID, sShopName);

		addButtons(nShopID, *pCard);
		addWorkers(nShopID, *pCard);

		vecCards.emplaceBack(pCard);
	}

	return vecCards;
}

QVector<Sity *> MainWindow::GetSities(int nClientID)
{
	QSqlQuery Sities_Query(m_db);
	QVector<Sity *> vecSities;

	Sities_Query.exec("SELECT DISTINCT t1.id, t1.Name FROM Shops as t2 "
						"JOIN Sities as t1 on t1.id = t2.Sity_id "
						"WHERE t2.Owner_id = " + QString::number(nClientID) + " ORDER BY t1.Name");

	while (Sities_Query.next()){
		auto nSityID = Sities_Query.value(0).toInt();
		auto sSityName = Sities_Query.value(1).toString();

		auto pSity = new Sity(this, nSityID, sSityName);
		pSity->SetCards(Add_Cards(nClientID, nSityID));
		vecSities.emplaceBack(pSity);
	}

	return vecSities;
}

QVector<ClientButton *> MainWindow::GetClients(){
	QSqlQuery Clients_Query(m_db);
	QVector<ClientButton *> vecClients;

	Clients_Query.exec("SELECT * FROM Clients ORDER BY Clients.Name");

	while (Clients_Query.next()){
		auto nID = Clients_Query.value(0).toInt();
		auto sClientName = Clients_Query.value(1).toString();

		auto pClient = new ClientButton(nullptr, nID, sClientName);
		vecClients.emplaceBack(pClient);
	}
	return vecClients;
}

bool MainWindow::read_DB(){
	m_db.setDatabaseName("./Sourse/main_db.db");

	if (!m_db.open()) {
		My_Error error("DB is offline");
		error.exec();
		return 0;
	}

	m_vecClientButtons = GetClients();
	auto layout = ui->scrollAreaWidgetContents->layout();
	for(auto item : m_vecClientButtons)
	{
		connect(item, SIGNAL(clicked()), this, SLOT(SetSities()));
		layout->addWidget(item);
	}

	if(!m_vecClientButtons.empty()){
		m_vecClientButtons[0]->clicked();
	}

	return 1;
}

//Menu Buttons
void MainWindow::on_Menu_1_triggered(){
	Reload_DB();
}

void MainWindow::on_Edit_DB_triggered(){
	edit_DB Edit_DB(m_db);
	Edit_DB.exec();
	Reload_DB();
}

void MainWindow::on_Delete_From_DB_triggered(){
	delete_db Delete_DB(m_db);
	Delete_DB.exec();
	Reload_DB();
}

