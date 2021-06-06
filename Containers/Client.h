#include <QTabWidget>
#include <QWidget>
#include "Containers/sity.h"


namespace Ui { class Client; }


class Client : public QWidget
{
	Q_OBJECT

	int id;
	QString name;
	QTabWidget Sities_Tab;


public:
	Sity *sities;
	int count;
	Ui::Client *ui;

	Client(QWidget *parent = nullptr);
	~Client();

	void addTab(int poz);
	void set_id(int _id){id = _id;}
	int get_id() {return id;}
	void set_count(int _count){count = _count;}
	int get_count() {return count;}
	void set_name(QString _name){name = _name;}
	QString get_name() {return name;}
};

