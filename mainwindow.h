#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Containers/client.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT
	QString path;
	Client *Clients;

public:
	MainWindow(QWidget *parent = nullptr);

	void set_path (QString P){
		path = P + "/AnyDesk.exe ";
	}

	bool read_DB(QString Folder);


	~MainWindow();

public slots:
	void open_connect();

private slots:
	void on_Need_Change_clicked();

private:
	Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
