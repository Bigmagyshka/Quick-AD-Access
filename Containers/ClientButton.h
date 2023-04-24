#ifndef CLIENTBUTTON_H
#define CLIENTBUTTON_H

#include <QPushButton>

class ClientButton : public QPushButton
{
	int m_nID {-1};
	QString m_sName;

public:
	ClientButton(QWidget *parent, int nID, const QString &sName);

	QString GetName() const;
	int GetID() const;
};

#endif // CLIENTBUTTON_H
