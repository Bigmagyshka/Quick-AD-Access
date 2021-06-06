#include "start_window.h"
#include "ui_start_window.h"
#include <QTimer>

start_Window::start_Window(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::start_Window){
	ui->setupUi(this);
	setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
	setModal(true);
}

void start_Window::set_pic(QString Folder, QString ver){
	QPixmap myPixmap( Folder + "/Sourse/logo.png" );
	ui->label_picture->setPixmap( myPixmap );
	ui->Version->setText(ver);
	ui->Author->setText("github.com/Bigmagyshka");
}

void start_Window::start(double t){
	QTimer::singleShot(t*1000, this, SLOT(close()));
	this->exec();
}

start_Window::~start_Window()
{
	delete ui;
}
