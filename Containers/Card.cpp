#include "QLabel"

#include "Containers/Card.h"
#include "ui_Card.h"
#include "Containers/ADButton.h"


Card::Card(QWidget *parent, int nID, const QString &sName) :
	QWidget(parent),
	ui(new Ui::Card)
{
	ui->setupUi(this);
	m_sName = sName;
	m_nID = nID;
	ui->card_1->setTitle(m_sName);
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
	auto sAdditionalInfo = QString::number(nConnectionID);
	auto pNewButton = new ADConnectButton(this, nConnectionID, sPassword, bIsAngry, sName, sAdditionalInfo);

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

