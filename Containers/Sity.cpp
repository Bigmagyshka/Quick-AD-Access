#include "Containers/Sity.h"
#include "ui_Sity.h"
#include "Containers/Card.h"

Sity::Sity(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::Sity){
	ui->setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose, true);
}

Sity::~Sity(){
	delete ui;
	delete [] cards;
}


void Sity::addCard(int poz){
	int row = poz / 3, column = poz % 3;
	ui->Default->addWidget(&cards[poz],row,column);
}

void Sity::remove(){
	for (int i = 0; i < count; i++)
	ui->Default->removeWidget(&cards[i]);
}
