#include "moveconnection.h"
#include "ui_moveconnection.h"

MoveConnection::MoveConnection(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::MoveConnection)
{
	ui->setupUi(this);
}

MoveConnection::~MoveConnection()
{
	delete ui;
}
