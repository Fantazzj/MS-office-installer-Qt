#ifndef LANGUAGESELECTOR_HPP
#define LANGUAGESELECTOR_HPP

#include "ui_installer.h"
#include "installer.hpp"
#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
	class languageSelector;
}
QT_END_NAMESPACE

class Installer;

class languageSelector : public QDialog {
	Q_OBJECT

public:
	languageSelector(QMainWindow* parent = nullptr);
	~languageSelector();

private slots:
	[[maybe_unused]] void on_buttonBox_accepted();
	[[maybe_unused]] void on_buttonBox_rejected();
	void reject() override;

private:
	Ui::languageSelector* ui;
	Installer* installer;
};


#endif//LANGUAGESELECTOR_HPP
