#include "Containers/sity.h"
#include "ui_sity.h"

Sity::Sity(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::Sity){
	ui->setupUi(this);
}

Sity::~Sity(){
	delete ui;
}


void Sity::addCard(int poz){
	int row = poz / 3, column = poz % 3;
	ui->Default->addWidget(&cards[poz],row,column);
}
