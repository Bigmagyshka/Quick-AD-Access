#pragma once
#include <QDialog>
#include <QTimer>

namespace Ui {class start_Window;}

class start_Window : public QDialog{
	Q_OBJECT

public:
	explicit start_Window(QWidget *parent = nullptr);
	explicit start_Window(QString ver);
	void start(double t);
	virtual ~start_Window();

private:
	Ui::start_Window *ui;
};
