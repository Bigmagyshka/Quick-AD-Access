#ifndef CARDDATA_H
#define CARDDATA_H
#include <QString>
#include <QSqlDatabase>
#include <QVector>

struct ADButtonData
{
	QString m_sName;
	int m_nConnectionID {0};
	QString m_sPassword;
	bool m_bIsAngry {false};
	QString m_sToolTip;
};

struct WorkersData
{
	QString m_sName;
	QString m_sNumber;
	QString m_sPosition;
};

struct CardData
{
	int m_nID {-1};
	QString m_sName;
	int m_nOwnerID {-1};
	int m_nSityID {-1};
	QString m_sAdditionalInfo;

	QVector<ADButtonData> m_vecButtonData;
	QVector<WorkersData> m_vecWorkerData;

	QSqlDatabase m_db;

	bool FindString(const QString &sToFind) const;
};

#endif // CARDDATA_H
