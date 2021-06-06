#ifndef CARD_H
#define CARD_H

#include <QWidget>
#include <QPushButton>


class my_button : public QPushButton{
	long id;
	bool is_angry;
	QString password;

public:
	explicit my_button(QWidget *parent);
	explicit my_button(QWidget *parent, long _id);
	void set_id(long z){id = z;}
	long get_id(){return id;}
	void set_pas(QString _pas){password = _pas;}
	QString get_pas(){return password;}
	void set_angry(bool _angry){is_angry = _angry;}
	bool get_angry(){return is_angry;}

	~my_button(){};
};


namespace Ui {
class Card;
}

class Card : public QWidget
{
	Q_OBJECT
	QString name;
	int id;
	int PC = 0, WP = 0;

public:
	my_button **buttons;

	explicit Card(QWidget *parent = nullptr);
	int add_PC(long _id, QString _password, QString _name, bool _angry);
	int add_WP(long _id, QString _password, QString _name, bool _angry);
	int add_Worker(QString Name, QString Position, QString Number);
	int get_PC(){return PC;};
	int get_WP(){return WP;};
	void set_name(QString _name);
	QString get_name() {return name;}
	void set_id(int _id){id = _id;}
	int get_id() {return id;}
	~Card();

private:
	Ui::Card *ui;
};

#endif // CARD_H
