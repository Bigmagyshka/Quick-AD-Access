#include "edit_db.h"
#include "ui_edit_db.h"

edit_DB::edit_DB(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::edit_DB)
{
	ui->setupUi(this);
}

edit_DB::~edit_DB()
{
	delete ui;
}
