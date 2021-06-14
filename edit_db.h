#ifndef EDIT_DB_H
#define EDIT_DB_H

#include <QDialog>

namespace Ui {
class edit_DB;
}

class edit_DB : public QDialog
{
	Q_OBJECT

public:
	explicit edit_DB(QWidget *parent = nullptr);
	~edit_DB();

private:
	Ui::edit_DB *ui;
};

#endif // EDIT_DB_H
