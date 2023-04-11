#pragma once
#include <QWidget>

class ADButton;

namespace Ui { class Card; }

class Card : public QWidget
{
	Q_OBJECT
	QString name;
	int id;
	int count_buttons = 0, max_count = 6;
	bool error = false;

public:
	ADButton *buttons;

	explicit Card(QWidget *parent = nullptr);
	void add_button(long _id, QString _password, QString _name, bool _angry);
	int add_Worker(QString Name, QString Position, QString Number);
	int get_count(){return count_buttons;};
	void set_name(QString _name);
	QString get_name() {return name;}
	void set_id(int _id){id = _id;}
	int get_id() {return id;}
	virtual ~Card();

private:
	Ui::Card *ui;
};
