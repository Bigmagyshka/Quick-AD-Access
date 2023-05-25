#pragma once
#include <QMainWindow>
#include <QSqlDatabase>
#include <QSettings>
#include "Containers/CardData.h"

namespace Ui { class MainWindow; }

class MainWindow : public QMainWindow
{
	Q_OBJECT
	QSettings m_objSettings;
	QVector<std::pair<QString, int>> m_vecClients;
	QMap<int, QString> m_mapSities;
	QMap<int, QSet<int>> m_mapSitiesByClient;
	QVector<CardData> m_vecCurCards;
	QSqlDatabase m_db;

	void addWorkers(int shop_id, CardData &cur_card);
	void addButtons(int shop_id, CardData &cur_card);

	void ReloadCards();
	void ReloadClients();
	void ReloadSities();

	void NeedChangeClients();
	void NeedChangeSity();
	void NeedChangeCards();

	void AddNewColumns() const;

public:
	MainWindow(QWidget *parent = nullptr);
	virtual ~MainWindow();

	bool read_DB();

public slots:
	void Reload_DB();

private slots:
	void on_Menu_1_triggered();
	void on_Edit_DB_triggered();
	void on_Delete_From_DB_triggered();
	void on_MoveConnection_triggered();

	void on_comboBox_Client_currentIndexChanged();
	void on_comboBox_Sity_currentIndexChanged();
	void on_textBrowser_Search_textChanged();

private:
	Ui::MainWindow *ui;
};
