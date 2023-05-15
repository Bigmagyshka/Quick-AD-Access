#include "addworker.h"
#include "ui_addworker.h"
#include "My_error.h"

AddWorker::AddWorker(int nShopID, QWidget *parent) :
	QDialog(parent), m_nShopID(nShopID), ui(new Ui::AddWorker)
{
	ui->setupUi(this);
}

QString AddWorker::GetName() const
{
	return ui->Name->toPlainText();
}

QString AddWorker::GetNumber() const
{
	return ui->Number->toPlainText();
}

QString AddWorker::GetPosition() const
{
	return ui->Position->toPlainText();
}


void AddWorker::on_Cansel_released()
{
	reject();
}


void AddWorker::on_Add_released()
{
	if(GetName().isEmpty()){
		My_Error error("Name can't be empty");
		error.exec();
		return;
	}
	if(GetNumber().isEmpty()){
		My_Error error("Number can't be empty");
		error.exec();
		return;
	}
	if(GetPosition().isEmpty()){
		My_Error error("Position can't be empty");
		error.exec();
		return;
	}

	accept();
}
