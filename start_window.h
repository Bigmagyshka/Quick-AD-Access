#ifndef START_WINDOW_H
#define START_WINDOW_H

#include <QDialog>

namespace Ui {
class start_Window;
}

class start_Window : public QDialog
{
	Q_OBJECT

public:
	explicit start_Window(QWidget *parent = nullptr);
	void set_pic(QString Folder, QString ver);
	void start(double t);
	~start_Window();

private:
	Ui::start_Window *ui;
};

#endif // START_WINDOW_H
