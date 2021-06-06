#include "Containers/card.h"
#include "ui_card.h"

my_button::my_button(QWidget *parent) :
	QPushButton(parent){
}

my_button::my_button(QWidget *parent, long _id) :
	QPushButton(parent){
	id = _id;
}


Card::Card(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::Card)
{
	ui->setupUi(this);	
	buttons = new my_button* [5];
	buttons[0] = ui->button_1;
	buttons[1] = ui->button_2;
	buttons[2] = ui->button_3;
	buttons[3] = ui->button_4;
	buttons[4] = ui->button_5;

	for (int i = 0; i < 5; i++)
		buttons[i]->hide();
}

int Card::add_PC(long _id, QString _password, QString _name, bool _angry){
	if (PC > 1) return -1;

	buttons[PC]->show();
	buttons[PC]->set_id(_id);
	if (!_name.isEmpty())
		buttons[PC]->setText(_name);
	buttons[PC]->set_pas(_password);
	buttons[PC++]->set_angry(_angry);
	return (PC-1);
}

int Card::add_WP(long _id, QString _password, QString _name, bool _angry){
	if (WP++ > 2) return false;

	buttons[WP + 1]->show();
	buttons[WP + 1]->set_id(_id);
	if (!_name.isEmpty())
		buttons[WP + 1]->setText(_name);
	buttons[WP + 1]->set_pas(_password);
	buttons[WP + 1]->set_angry(_angry);
	return (WP-1);
}

int Card::add_Worker(QString Name, QString Position, QString Number){
	ui->table_card_1->insertRow(ui->table_card_1->rowCount());
	ui->table_card_1->setItem(ui->table_card_1->rowCount()-1, 0, new QTableWidgetItem(Name));
	ui->table_card_1->setItem(ui->table_card_1->rowCount()-1, 2, new QTableWidgetItem(Position));
	ui->table_card_1->setItem(ui->table_card_1->rowCount()-1, 1, new QTableWidgetItem(Number));
	return 1;
}

void Card::set_name(QString _name){
	name = _name;
	ui->card_1->setTitle(name);
}

Card::~Card(){
	delete ui;
}
