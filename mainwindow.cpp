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
#include "Containers/Card.h"
#include "Containers/ADButton.h"
#include "EditDB/moveconnection.h"

#ifndef __linux__
#include "windows.h"
#endif

void Run(QString path);
void Ask(QString path);

void MainWindow::AddNewColumns() const
{
	QSqlQuery objQuery(m_db);

	objQuery.exec("SELECT EXISTS (SELECT * FROM sqlite_master WHERE tbl_name = 'Shops' AND sql LIKE '%AdditionalInfo%')");
	objQuery.next();

	auto bIsAdditionalInfoExist = objQuery.value(0).toBool();
	if(!bIsAdditionalInfoExist)
		objQuery.exec("ALTER TABLE Shops ADD COLUMN AdditionalInfo TEXT");
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
	ui->setupUi(this);
	m_db = QSqlDatabase::addDatabase("QSQLITE");

	restoreGeometry(m_objSettings.value("MainWindow/geometry").toByteArray());
	restoreState(m_objSettings.value("MainWindow/windowState").toByteArray());
}

MainWindow::~MainWindow(){
	delete ui;

	m_objSettings.setValue("MainWindow/geometry", saveGeometry());
	m_objSettings.setValue("MainWindow/windowState", saveState());
}

//Base Functions
void MainWindow::Reload_DB(){
	read_DB();
}

// Add main data from DB
void MainWindow::addButtons(int shop_id, CardData &cur_card){
	QSqlQuery Query(m_db);

	Query.exec("SELECT * FROM Work_Places WHERE Work_Places.Shop_id = " + QString::number(shop_id) + " ORDER BY Work_Places.Is_PC DESC");

	while(Query.next())
	{
		ADButtonData obj;
		obj.m_nConnectionID = Query.value(2).toLongLong();
		obj.m_sPassword = Query.value(3).toString();
		obj.m_sName = Query.value(4).toString();
		obj.m_bIsAngry = Query.value(5).toBool();
		obj.m_sToolTip = QString::number(obj.m_nConnectionID);

		cur_card.m_vecButtonData.emplaceBack(obj);
	}
}

void MainWindow::addWorkers(int shop_id, CardData &cur_card){
	QSqlQuery Query(m_db);

	Query.exec("SELECT * FROM Workers WHERE Workers.Shop_id = " + QString::number(shop_id));

	while (Query.next())
	{
		WorkersData obj;
		obj.m_sName = Query.value(1).toString();
		obj.m_sPosition = Query.value(3).toString();
		obj.m_sNumber = Query.value(2).toString();

		cur_card.m_vecWorkerData.emplaceBack(obj);
	}
}

void MainWindow::ReloadCards()
{
	m_vecCurCards.clear();

	QSqlQuery Cards_Query(m_db);
	Cards_Query.exec("SELECT * FROM Shops ORDER BY Shops.Address");
	auto pLayout = dynamic_cast<QGridLayout *>(ui->scrollArea_Shops->widget()->layout());

	while (Cards_Query.next()){
		CardData obj;
		obj.m_nID = Cards_Query.value(0).toInt();
		obj.m_sName = Cards_Query.value(1).toString();
		obj.m_nOwnerID = Cards_Query.value(2).toInt();
		obj.m_nSityID = Cards_Query.value(3).toInt();
		obj.m_sAdditionalInfo = Cards_Query.value(4).toString();
		obj.m_db = m_db;

		addButtons(obj.m_nID, obj);
		addWorkers(obj.m_nID, obj);

		pLayout->addWidget(new Card(obj), m_vecCurCards.size()/2, m_vecCurCards.size()%2);
		m_vecCurCards.emplaceBack(obj);
	}
}

void MainWindow::ReloadClients()
{
	auto pComboClient = ui->comboBox_Client;

	QSqlQuery Clients_Query(m_db);
	Clients_Query.exec("SELECT * FROM Clients where id in (select Owner_id from shops) ORDER BY Clients.Name");

	pComboClient->clear();
	m_vecClients.clear();
	pComboClient->addItem("", -1);

	while (Clients_Query.next()){
		auto nID = Clients_Query.value(0).toInt();
		auto sClientName = Clients_Query.value(1).toString();

		pComboClient->addItem(sClientName, nID);
		m_vecClients.emplaceBack(sClientName, nID);
	}
}

void MainWindow::ReloadSities()
{
	auto pComboSity = ui->comboBox_Sity;

	QSqlQuery objQuerySity(m_db);
	objQuerySity.exec("SELECT * FROM Sities where id in (select Sity_id from shops) ORDER BY Sities.Name");

	pComboSity->clear();
	m_vecSities.clear();
	pComboSity->addItem("", -1);

	while (objQuerySity.next()){
		auto nID = objQuerySity.value(0).toInt();
		auto sSityName = objQuerySity.value(1).toString();

		pComboSity->addItem(sSityName, nID);
		m_vecSities.emplaceBack(sSityName, nID);
	}
}

bool MainWindow::read_DB(){
	m_db.setDatabaseName("./Sourse/main_db.db");

	if (!m_db.open()) {
		My_Error error("DB is offline");
		error.exec();
		return false;
	}

	AddNewColumns();

	ReloadClients();
	ReloadSities();
	ReloadCards();
	ui->textBrowser_Search->clear();
	m_db.close();

	return true;
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


void MainWindow::on_MoveConnection_triggered()
{
	MoveConnection dlg(m_db);
	dlg.exec();
	Reload_DB();
}

void MainWindow::NeedChangeClients()
{

}

void MainWindow::NeedChangeSity()
{

}

void MainWindow::NeedChangeCards()
{
	auto nClientID = ui->comboBox_Client->currentData().toInt();
	auto nSityID = ui->comboBox_Sity->currentData().toInt();
	auto sSearchText = ui->textBrowser_Search->toPlainText();

	ui->scrollArea_Shops->widget()->deleteLater();

	auto pNewLayout = new QGridLayout;
	auto pNewWidget = new QWidget;

	for(int nIndex{0}, nAddedItems{0}; nIndex < m_vecCurCards.size(); ++nIndex)
	{
		auto objCard = m_vecCurCards[nIndex];

		if(nClientID > 0 && objCard.m_nOwnerID != nClientID)
			continue;

		if(nSityID > 0 && objCard.m_nSityID != nSityID)
			continue;

		if(!sSearchText.isEmpty() && !objCard.FindString(sSearchText))
			continue;

		pNewLayout->addWidget(new Card(objCard), nAddedItems/2, nAddedItems%2);
		++nAddedItems;
	}

	pNewWidget->setLayout(pNewLayout);
	ui->scrollArea_Shops->setWidget(pNewWidget);
}

void MainWindow::on_comboBox_Client_currentIndexChanged()
{
	NeedChangeSity();
	NeedChangeCards();
}


void MainWindow::on_comboBox_Sity_currentIndexChanged()
{
	NeedChangeClients();
	NeedChangeCards();
}


void MainWindow::on_textBrowser_Search_textChanged()
{
	NeedChangeCards();
}

