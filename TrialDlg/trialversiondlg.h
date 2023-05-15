#ifndef TRIALVERSIONDLG_H
#define TRIALVERSIONDLG_H

#include <QDialog>

namespace Ui {
	class TrialVersionDlg;
}

class TrialVersionDlg : public QDialog
{
	Q_OBJECT

public:
	explicit TrialVersionDlg(QWidget *parent = nullptr);
	~TrialVersionDlg();

	void start(double t);

private:
	Ui::TrialVersionDlg *ui;
};

#endif // TRIALVERSIONDLG_H
