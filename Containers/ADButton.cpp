#include "ADButton.h"

ADButton::ADButton(QWidget *parent) : QPushButton(parent){}

ADButton::ADButton() : QPushButton(nullptr){}

void ADButton::set_id(long z){id = z;}

long ADButton::get_id(){return id;}

void ADButton::set_pas(QString _pas){password = _pas;}

QString ADButton::get_pas(){return password;}

void ADButton::set_angry(bool _angry){is_angry = _angry;}

bool ADButton::get_angry(){return is_angry;}
