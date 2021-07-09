#include "ask.h"
#include "ui_ask.h"

ask::ask(QWidget *parent) :
	QDialog(parent), ui(new Ui::ask){
	ui->setupUi(this);
	this->setModal(1);
	setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
}

ask::ask(bool &_flag, QString Question) :
	QDialog(nullptr), ui(new Ui::ask){
	ui->setupUi(this);
	this->setModal(1);
	setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
	flag = &_flag;
	ui->Question->setText(Question);
}

ask::ask(bool &_flag, QString Question, QString Answer_1, QString Answer_2) :
	QDialog(nullptr), ui(new Ui::ask){

	ui->setupUi(this);
	this->setModal(1);
	setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
	flag = &_flag;
	ui->Question->setText(Question);
	ui->pushButton->setText(Answer_1);
	ui->pushButton_2->setText(Answer_2);
}


ask::~ask()
{
	delete ui;
}

void ask::on_pushButton_clicked()
{
   *flag = false;
	close();
}

void ask::on_pushButton_2_clicked()
{
   *flag = true;
	close();
}
