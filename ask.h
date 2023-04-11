#pragma once
#include <QDialog>

namespace Ui {
class ask;
}

class ask : public QDialog
{
	Q_OBJECT

public:
	bool *flag;
	explicit ask(QWidget *parent = nullptr);
	ask(bool &_flag, QString Question);
	ask(bool &_flag, QString Question, QString Answer_1, QString Answer_2);
	void set_f(bool &k){flag = &k;}
	virtual ~ask();

private slots:
	void on_pushButton_clicked();

	void on_pushButton_2_clicked();

private:
	Ui::ask *ui;
};
