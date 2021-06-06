#include "Containers/client.h"
#include "ui_client.h"


Client::Client(QWidget *parent):
	QWidget(parent),
	ui(new Ui::Client)
{
	ui->setupUi(this);
}

Client::~Client(){
	delete ui;
 }

void Client::addTab(int poz){
	ui->Sities->addTab(&sities[poz],sities[poz].get_name());
}
