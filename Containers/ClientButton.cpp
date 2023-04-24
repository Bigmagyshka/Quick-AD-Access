#include "ClientButton.h"

ClientButton::ClientButton(QWidget *parent, int nID, const QString &sName)
	: QPushButton(parent), m_nID(nID), m_sName(sName)
{
	setText(sName);
}

QString ClientButton::GetName() const
{
	return m_sName;
}

int ClientButton::GetID() const
{
	return m_nID;
}
