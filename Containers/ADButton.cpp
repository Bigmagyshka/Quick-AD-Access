#include "ADButton.h"
#include "ask.h"
#include <thread>

ADConnectButton::ADConnectButton(QWidget *parent, int nConnectionID, const QString &sPassword, bool bIsAngry, const QString &sName, const QString &sAddittionalInfo)
	: QPushButton(parent), m_sName(sName), m_nConnectionID(nConnectionID), m_sPassword(sPassword), m_bIsAngry(bIsAngry), m_sAddittionalInfo(sAddittionalInfo)
{
	connect(this, SIGNAL(released()), this, SLOT(open_connect()));
	setText(sName);
	setToolTip(sAddittionalInfo);
	setToolTipDuration(10000);
	setMaximumWidth(150);
}

long ADConnectButton::GetConnectionID() const {
	return m_nConnectionID;
}

QString ADConnectButton::GetPassword() const {
	return m_sPassword;
}

bool ADConnectButton::GetIsAngry() const {
	return m_bIsAngry;
}

void ADConnectButton::kill()
{
	std::this_thread::sleep_for(std::chrono::milliseconds(3000));
	system("taskkill /IM cmd.exe");
}

void ADConnectButton::Run(QString path) const
{
	std::thread thr1(system,path.toLocal8Bit().data()), thr2(ADConnectButton::kill);
	thr1.detach();
	thr2.detach();
}

void ADConnectButton::Ask(QString path) const
{
	bool k;
	ask Ask(k,"Управляющий требует, чтобы перед подключением к кассе ему позвонили !!!");
	Ask.exec();
	if (k) Run(path);
}

void ADConnectButton::open_connect() const
{
	auto sConnect = QString("echo " + m_sPassword + " | " + ".\\AnyDesk.exe " + QString::number(m_nConnectionID) + + " --with-password");
	m_bIsAngry ? Ask(sConnect) : Run(sConnect);
}
