#include "additionalinfodlg.h"
#include "ui_additionalinfodlg.h"

AdditionalInfoDlg::AdditionalInfoDlg(const QString &sText, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::AdditionalInfoDlg)
{
	ui->setupUi(this);
	ui->text_Info->setText(sText);
}

QString AdditionalInfoDlg::GetText() const
{
	return ui->text_Info->toPlainText();
}
