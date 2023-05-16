#include "QLabel"
#include <QSqlQuery>

#include "Containers/Card.h"
#include "ui_Card.h"
#include "Containers/ADButton.h"
#include "Containers/AdditionalInfoDlg.h"
#include "My_error.h"

Card::Card(QWidget *parent, int nID, const QString &sName, const QString &sAdditionalInfo, QSqlDatabase &db) :
	QWidget(parent), m_nID(nID), m_sAdditionalInfo(sAdditionalInfo), m_db(db), ui(new Ui::Card)
{
	ui->setupUi(this);
	ui->card_1->setTitle(sName);
	ui->table_card_1->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

Card::Card(CardData &obj) :
	QWidget(), ui(new Ui::Card)
{
	ui->setupUi(this);
	ui->card_1->setTitle(obj.m_sName);
	ui->table_card_1->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

	m_nID = obj.m_nID;
	m_sAdditionalInfo = obj.m_sAdditionalInfo;
	m_db = obj.m_db;

	for(auto objButtonData : obj.m_vecButtonData)
		add_button(objButtonData.m_nConnectionID, objButtonData.m_sPassword, objButtonData.m_sName, objButtonData.m_bIsAngry);

	for(auto objWorkerData : obj.m_vecWorkerData)
		add_Worker(objWorkerData.m_sName, objWorkerData.m_sPosition, objWorkerData.m_sNumber);

	m_pDataParent = &obj;
}

bool Card::add_button(long nConnectionID, const QString &sPassword, QString sName, bool bIsAngry)
{
	if (m_nCurButtonCount == m_nMaxButtonCount)
		return false;

	auto sToolTip = QString::number(nConnectionID);
	auto pNewButton = new ADConnectButton(this, nConnectionID, sPassword, bIsAngry, sName, sToolTip);

	int nMaxButtonsInColumn = m_nMaxButtonCount / m_nColumns;
	int nRow = m_nCurButtonCount%nMaxButtonsInColumn;
	int nColumn = m_nCurButtonCount/nMaxButtonsInColumn;
	ui->gridLayout_Buttons->addWidget(pNewButton, nRow, nColumn);
	m_vecButtons.emplaceBack(pNewButton);
	++m_nCurButtonCount;
	return true;
}

bool Card::add_Worker(QString Name, QString Position, QString Number){
	auto pTable = ui->table_card_1;
	pTable->insertRow(pTable->rowCount());
	pTable->setItem(pTable->rowCount()-1, 0, new QTableWidgetItem(Name));
	pTable->setItem(pTable->rowCount()-1, 1, new QTableWidgetItem(Number));
	pTable->setItem(pTable->rowCount()-1, 2, new QTableWidgetItem(Position));
	return true;
}

void Card::on_pushButton_released()
{
	if (!m_db.open()) {
		My_Error error("DB is offline");
		error.exec();
		return;
	}

	AdditionalInfoDlg dlg(m_sAdditionalInfo);
	if(dlg.exec() && m_sAdditionalInfo != dlg.GetText())
	{
		m_sAdditionalInfo = dlg.GetText();
		QSqlQuery Query(m_db);
		auto sQuery = "UPDATE Shops SET AdditionalInfo = '" + m_sAdditionalInfo + "' WHERE id = " + QString::number(m_nID);
		Query.exec(sQuery);

		if(m_pDataParent)
			m_pDataParent->m_sAdditionalInfo = m_sAdditionalInfo;
	}

	m_db.close();
}

