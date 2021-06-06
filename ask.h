#ifndef ASK_H
#define ASK_H

#include <QDialog>

namespace Ui {
class ask;
}

class ask : public QDialog
{
	Q_OBJECT

public:
	int *flag;
	explicit ask(QWidget *parent = nullptr);
	void set_f(int *k){flag = k;}
	~ask();

private slots:
	void on_pushButton_clicked();

	void on_pushButton_2_clicked();

private:
	Ui::ask *ui;
};

#endif // ASK_H
