#include "QLabel"

#include "Containers/Card.h"
#include "ui_Card.h"

my_button::my_button(QWidget *parent) :
	QPushButton(parent){
}

my_button::my_button() :
	QPushButton(nullptr){
}



Card::Card(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::Card)
{
	ui->setupUi(this);
	buttons = new my_button[max_count];
	setAttribute(Qt::WA_DeleteOnClose, true);
}


void Card::add_button(long _id, QString _password, QString _name, bool _angry){
	if (count_buttons == max_count) {
		if (!error){
			ui->button_box->addWidget(new QLabel("Превышен лимит кнопок"));
			error = !error;
		}
		return;
	}
	buttons[count_buttons].set_id(_id);
	if (!_name.isEmpty())
	buttons[count_buttons].setText(_name);
	buttons[count_buttons].set_pas(_password);
	buttons[count_buttons].set_angry(_angry);
	buttons[count_buttons].setToolTip(QString::number(buttons[count_buttons].get_id()));
	buttons[count_buttons].setToolTipDuration(5000);
	ui->button_box->addWidget(&buttons[count_buttons]);
	count_buttons++;
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
	delete[] buttons;
 }
