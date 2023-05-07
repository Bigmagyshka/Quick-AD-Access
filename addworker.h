#ifndef ADDWORKER_H
#define ADDWORKER_H

#include <QDialog>

namespace Ui {
	class AddWorker;
}

class AddWorker : public QDialog
{
	Q_OBJECT
	int m_nShopID {-1};

public:
	AddWorker(int nShopID, QWidget *parent = nullptr);
	virtual ~AddWorker() = default;

	QString GetName() const;
	QString GetNumber() const;
	QString GetPosition() const;

private slots:
	void on_Cansel_released();

	void on_Add_released();

private:
	Ui::AddWorker *ui;
};

#endif // ADDWORKER_H
