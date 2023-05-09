#ifndef ADDITIONALINFODLG_H
#define ADDITIONALINFODLG_H

#include <QDialog>

namespace Ui {
	class AdditionalInfoDlg;
}

class AdditionalInfoDlg : public QDialog
{
	Q_OBJECT

public:
	AdditionalInfoDlg(const QString &sText, QWidget *parent = nullptr);
	~AdditionalInfoDlg() = default;

	QString GetText() const;
private:
	Ui::AdditionalInfoDlg *ui;
};

#endif // ADDITIONALINFODLG_H
