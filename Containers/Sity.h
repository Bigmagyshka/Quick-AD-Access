#pragma once
#include <QWidget>

class Card;
namespace Ui {class Sity;}

class Sity : public QWidget
{
	Q_OBJECT
	int id;
	QString name;

public:
	explicit Sity(QWidget *parent = nullptr);
	Card *cards;
	int count;

	void addCard(int poz);
	void remove();
	void set_id(int _id){id = _id;}
	int get_id() {return id;}
	void set_count(int _count){count = _count;}
	int get_count() {return count;}
	void set_name(QString _name){name = _name;}
	QString get_name() {return name;}

	~Sity();

private:
	Ui::Sity *ui;
};
