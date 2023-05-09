#pragma once
#include <QMainWindow>
#include <QSqlDatabase>

class ClientButton;
class Sity;
class Card;

namespace Ui { class MainWindow; }

class MainWindow : public QMainWindow
{
	Q_OBJECT
	QVector<ClientButton *> m_vecClientButtons;
	QVector<Sity *> m_vecCurSities;
	QSqlDatabase m_db;
	ClientButton *m_pLastSelectedButton {nullptr};

	void addWorkers(int shop_id, Card &cur_card);
	void addButtons(int shop_id, Card &cur_card);

	QVector<Card *> Add_Cards(int id_client, int id_sity);
	QVector<Sity *> GetSities(int nClientID);
	QVector<ClientButton *> GetClients();

	void AddNewColumns() const;

public:
	MainWindow(QWidget *parent = nullptr);

	bool read_DB();


	virtual ~MainWindow() = default;

public slots:
	void Reload_DB();
	void SetSities();

private slots:
	void on_Menu_1_triggered();
	void on_Edit_DB_triggered();
	void on_Delete_From_DB_triggered();

	void on_MoveConnection_triggered();

private:
	Ui::MainWindow *ui;
};
