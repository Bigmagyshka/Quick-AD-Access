#pragma once

#include <QDialog>

namespace Ui {
class My_Error;
}

class My_Error : public QDialog
{
	Q_OBJECT

public:
	explicit My_Error(QWidget *parent = nullptr);
	explicit My_Error(QString text);
	~My_Error();

private slots:
	void on_pushButton_clicked();

private:
	Ui::My_Error *ui;
};
