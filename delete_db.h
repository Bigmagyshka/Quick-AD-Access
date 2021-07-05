#ifndef DELETE_DB_H
#define DELETE_DB_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QSqlDriver>

namespace Ui {
class delete_db;
}

class delete_db : public QDialog
{
	Q_OBJECT

public:
	explicit delete_db(QWidget *parent = nullptr);
	delete_db (QSqlDatabase &db);
	~delete_db();

private:
	Ui::delete_db *ui;
	QSqlDatabase db;

	int Client = -1, Sity = -1, Shop = -1;
	QString Connection, Number;
};

#endif // DELETE_DB_H
