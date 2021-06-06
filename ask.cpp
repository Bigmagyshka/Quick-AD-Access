#include "ask.h"
#include "ui_ask.h"

ask::ask(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::ask)
{
	ui->setupUi(this);
	this->setModal(1);
	setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
}

ask::~ask()
{
	delete ui;
}

void ask::on_pushButton_clicked()
{
   *flag = 0;
	close();
}

void ask::on_pushButton_2_clicked()
{
   *flag = 1;
	close();
}
