#include "Containers/Sity.h"
#include "ui_Sity.h"
#include "Containers/Card.h"

Sity::Sity(QWidget *parent, int nID, const QString sName) :
	QWidget(parent), m_nID(nID), m_sName(sName), ui(new Ui::Sity)
{
	ui->setupUi(this);
}

void Sity::SetCards(const QVector<Card *> &vecCards)
{
	m_vecCards = vecCards;

	for(int nPoz{0}; nPoz < m_vecCards.size(); ++nPoz)
	{
		int row = nPoz / 3, column = nPoz % 3;
		ui->Default->addWidget(m_vecCards[nPoz],row,column);
	}
}

QString Sity::GetName() const
{
	return m_sName;
}
