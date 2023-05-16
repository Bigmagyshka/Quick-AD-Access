#include "ADButton.h"
#include "ask.h"
#include <thread>
#include "TrialDlg/trialversiondlg.h"

bool gTrial = true;

ADConnectButton::ADConnectButton(QWidget *parent, int nConnectionID, const QString &sPassword, bool bIsAngry, const QString &sName, const QString &sToolTip)
	: QPushButton(parent), m_sName(sName), m_nConnectionID(nConnectionID), m_sPassword(sPassword), m_bIsAngry(bIsAngry), m_sToolTip(sToolTip)
{
	connect(this, SIGNAL(released()), this, SLOT(open_connect()));
	setText(sName);
	setToolTip(sToolTip);
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
	if(gTrial)
	{
		TrialVersionDlg dlg;
		dlg.start(1.5);

		auto seconds = time(NULL);
		auto timeinfo = localtime(&seconds);

		if(timeinfo->tm_year > 2023)
			return;

		if(timeinfo->tm_mon > 5)
			return;

		if(timeinfo->tm_mday > 27)
			return;
	}

	auto sConnect = QString("echo " + m_sPassword + " | " + ".\\AnyDesk.exe " + QString::number(m_nConnectionID) + + " --with-password");
	m_bIsAngry ? Ask(sConnect) : Run(sConnect);
}
