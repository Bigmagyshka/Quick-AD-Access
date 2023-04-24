#pragma once
#include <QWidget>

class Card;
namespace Ui {class Sity;}

class Sity : public QWidget
{
	Q_OBJECT
	int m_nID {-1};
	QString m_sName;
	QVector<Card *> m_vecCards;

public:
	Sity(QWidget *parent, int nID, const QString sName);

	void SetCards(const QVector<Card *> &vecCards);
	QString GetName() const;

	virtual ~Sity() = default;

private:
	Ui::Sity *ui;
};
