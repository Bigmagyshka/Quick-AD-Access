#pragma once
#include <QPushButton>

class ADButton : public QPushButton{
	long id {0};
	bool is_angry {false};
	QString password;

public:
	explicit ADButton(QWidget *parent);
	explicit ADButton();
	void set_id(long z);
	long get_id();
	void set_pas(QString _pas);
	QString get_pas();
	void set_angry(bool _angry);
	bool get_angry();

	virtual ~ADButton() = default;
};
