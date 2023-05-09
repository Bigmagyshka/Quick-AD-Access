#include "QLabel"
#include <QSqlQuery>

#include "Containers/Card.h"
#include "ui_Card.h"
#include "Containers/ADButton.h"
#include "Containers/additionalinfodlg.h"

Card::Card(QWidget *parent, int nID, const QString &sName, const QString &sAdditionalInfo, QSqlDatabase &db) :
	QWidget(parent), m_sName(sName), m_nID(nID), m_sAdditionalInfo(sAdditionalInfo), m_db(db), ui(new Ui::Card)
{
	ui->setupUi(this);
	ui->card_1->setTitle(sName);
}

bool Card::add_button(long nConnectionID, const QString &sPassword, QString sName, bool bIsAngry)
{
	if (m_nCurButtonCount == m_nMaxButtonCount)
	{
		if (!m_bIsError){
			ui->button_box->addWidget(new QLabel("Превышен лимит кнопок"));
			m_bIsError = !m_bIsError;
		}
		return false;
	}
	auto sToolTip = QString::number(nConnectionID);
	auto pNewButton = new ADConnectButton(this, nConnectionID, sPassword, bIsAngry, sName, sToolTip);

	ui->button_box->addWidget(pNewButton);
	m_vecButtons.emplaceBack(pNewButton);
	++m_nCurButtonCount;
	return true;
}

bool Card::add_Worker(QString Name, QString Position, QString Number){
	ui->table_card_1->insertRow(ui->table_card_1->rowCount());
	ui->table_card_1->setItem(ui->table_card_1->rowCount()-1, 0, new QTableWidgetItem(Name));
	ui->table_card_1->setItem(ui->table_card_1->rowCount()-1, 2, new QTableWidgetItem(Position));
	ui->table_card_1->setItem(ui->table_card_1->rowCount()-1, 1, new QTableWidgetItem(Number));
	return true;
}

QString Card::GetName() const {return m_sName;}


void Card::on_pushButton_released()
{
	AdditionalInfoDlg dlg(m_sAdditionalInfo);
	if(dlg.exec() && m_sAdditionalInfo != dlg.GetText())
	{
		m_sAdditionalInfo = dlg.GetText();
		QSqlQuery Query(m_db);
		auto sQuery = "UPDATE Shops SET AdditionalInfo = '" + m_sAdditionalInfo + "' WHERE id = " + QString::number(m_nID);
		Query.exec(sQuery);
	}
}

