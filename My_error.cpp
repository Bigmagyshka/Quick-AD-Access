#include "My_error.h"
#include "ui_My_error.h"

My_Error::My_Error(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::My_Error)
{
	ui->setupUi(this);
	this->setModal(1);
	setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
}

My_Error::~My_Error()
{
	delete ui;
}

void My_Error::on_pushButton_clicked()
{
	this->close();
}
