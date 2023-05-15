#include "trialversiondlg.h"
#include "ui_trialversiondlg.h"
#include <QTimer>

TrialVersionDlg::TrialVersionDlg(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::TrialVersionDlg)
{
	ui->setupUi(this);
}

TrialVersionDlg::~TrialVersionDlg()
{
	delete ui;
}

void TrialVersionDlg::start(double t){
	QTimer::singleShot(t*1000, this, SLOT(close()));
	this->exec();
}
