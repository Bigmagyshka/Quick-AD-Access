#ifndef MOVECONNECTION_H
#define MOVECONNECTION_H

#include <QDialog>

namespace Ui {
	class MoveConnection;
}

class MoveConnection : public QDialog
{
	Q_OBJECT

public:
	explicit MoveConnection(QWidget *parent = nullptr);
	~MoveConnection();

private:
	Ui::MoveConnection *ui;
};

#endif // MOVECONNECTION_H
