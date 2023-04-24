#pragma once
#include <QPushButton>

class ADConnectButton : public QPushButton
{
	QString m_sName;
	int m_nConnectionID {0};
	QString m_sPassword;
	bool m_bIsAngry {false};
	QString m_sAddittionalInfo;

	static void kill();
	void Run(QString path) const;
	void Ask(QString path) const;

public:
	ADConnectButton(QWidget *parent, int nConnectionID, const QString &sPassword, bool bIsAngry, const QString &sName, const QString &sAddittionalInfo);

	long GetConnectionID() const;
	QString GetPassword() const;
	bool GetIsAngry() const;

	virtual ~ADConnectButton() = default;

public slots:
	void open_connect() const;
};
