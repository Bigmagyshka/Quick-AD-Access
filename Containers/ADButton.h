#pragma once
#include <QPushButton>

class ADConnectButton : public QPushButton
{
	Q_OBJECT

	QString m_sName;
	int m_nConnectionID {0};
	QString m_sPassword;
	bool m_bIsAngry {false};
	QString m_sToolTip;

	static void kill();
	void Run(QString path) const;
	void Ask(QString path) const;

public:
	ADConnectButton(QWidget *parent, int nConnectionID, const QString &sPassword, bool bIsAngry, const QString &sName, const QString &sToolTip);

	long GetConnectionID() const;
	QString GetPassword() const;
	bool GetIsAngry() const;

	virtual ~ADConnectButton() = default;

private slots:
	void open_connect() const;
};
