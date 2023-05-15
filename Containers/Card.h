#pragma once
#include <QWidget>
#include <QSqlDatabase>
#include "Containers/CardData.h"

class ADConnectButton;

namespace Ui { class Card; }

class Card : public QWidget
{
	Q_OBJECT
	CardData *m_pDataParent {nullptr};

	int m_nCurButtonCount {0};
	const int m_nMaxButtonCount {10};
	int m_nID {-1};
	QString m_sAdditionalInfo;
	QSqlDatabase m_db;

public:
	QVector<ADConnectButton *> m_vecButtons;

	Card(QWidget *parent, int nID, const QString &sName, const QString &sAdditionalInfo, QSqlDatabase &db);
	Card(CardData &obj);

	bool add_button(long nID, const QString &sPassword, QString sName, bool bIsAngry);
	bool add_Worker(QString Name, QString Position, QString Number);

	virtual ~Card() = default;

private slots:
	void on_pushButton_released();

private:
	Ui::Card *ui {nullptr};
};
