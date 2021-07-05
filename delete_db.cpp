#include "delete_db.h"
#include "ui_delete_db.h"

delete_db::delete_db(QWidget *parent) : QDialog(parent), ui(new Ui::delete_db){
	ui->setupUi(this);
}

delete_db::delete_db(QSqlDatabase &db) : QDialog(), ui(new Ui::delete_db){

	ui->setupUi(this);
	setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
	setModal(true);
	this->db = db;


	ui->Clients->setColumnWidth(0,10);
	ui->Sities->setColumnWidth(0,10);
	ui->Shops->setColumnWidth(0,10);
}

delete_db::~delete_db(){
	delete ui;
}
