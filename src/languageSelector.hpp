#ifndef LANGUAGESELECTOR_HPP
#define LANGUAGESELECTOR_HPP

#include "installer.hpp"
#include "ui_installer.h"
#include <QDialog>
#include <QScrollArea>

QT_BEGIN_NAMESPACE
namespace Ui {
	class languageSelector;
}
QT_END_NAMESPACE

class Installer;

enum CallType {
	None,
	Product,
	Proofing
};

class languageSelector : public QDialog {
	Q_OBJECT

public:
	languageSelector(QMainWindow* parent = nullptr, CallType callType = None);
	~languageSelector();

private slots:
	[[maybe_unused]] void on_buttonBox_accepted();
	[[maybe_unused]] void on_buttonBox_rejected();
	void reject() override;

private:
	Ui::languageSelector* ui;
	Installer* installer;
	CallType callType;
	QVector<QCheckBox*> checkBoxLangs;
	void widgetPopulator(QScrollArea* scrollArea);
};

#endif//LANGUAGESELECTOR_HPP
