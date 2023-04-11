#include "Containers/Client.h"
#include "ui_Client.h"
#include "Containers/Sity.h"

Client::Client(QWidget *parent):
	QWidget(parent),
	ui(new Ui::Client)
{
	ui->setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose, true);
}

Client::~Client(){
	delete ui;
	delete [] sities;
}

void Client::addTab(int poz){
	ui->Sities->addTab(&sities[poz],sities[poz].get_name());
}

void Client::remove(){
	for (int i = 0; i < count; i++)
		ui->Sities->removeTab(i);
}

int Client::get_index(){
	return ui->Sities->currentIndex();
}

void Client::set_index(int ind){
	if (ind <= ui->Sities->count())
		ui->Sities->setCurrentIndex(ind);
}
