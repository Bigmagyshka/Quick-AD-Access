#ifndef EDIT_DB_H
#define EDIT_DB_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QSqlDriver>

namespace Ui {
class edit_DB;
}

class edit_DB : public QDialog
{
	Q_OBJECT

public:
	explicit edit_DB(QWidget *parent = nullptr);
	edit_DB (QSqlDatabase &db);
	~edit_DB();

private slots:
	void on_pushButton_5_clicked();

	void on_pushButton_4_clicked();

	void on_DB_Clients_cellChanged(int row, int column);

private:
	Ui::edit_DB *ui;
	QSqlDatabase db;
	bool flag = false;
};

#endif // EDIT_DB_H
