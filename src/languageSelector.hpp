#ifndef LANGUAGESELECTOR_HPP
#define LANGUAGESELECTOR_HPP

#include "ui_installer.h"
#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
	class languageSelector;
}
QT_END_NAMESPACE

class languageSelector : public QDialog {
	Q_OBJECT

public:
	languageSelector(QMainWindow* parent = nullptr, Ui::Installer* installerUi = nullptr);
	~languageSelector();

private slots:
	void on_buttonBox_accepted();
	void on_buttonBox_rejected();
	void reject() override;

private:
	Ui::languageSelector* ui;
	Ui::Installer* installerUi;
};


#endif//LANGUAGESELECTOR_HPP
