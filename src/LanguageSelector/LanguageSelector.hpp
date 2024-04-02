#ifndef LANGUAGESELECTOR_HPP
#define LANGUAGESELECTOR_HPP

#include <QDialog>
#include <QScrollArea>

#include "src/DataModel/DataModel.hpp"
#include "src/Installer/Installer.hpp"
#include "../Installer/ui_installer.h"

QT_BEGIN_NAMESPACE
namespace Ui {
	class LanguageSelector;
}
QT_END_NAMESPACE

class Installer;

enum CallType {
	None,
	Product,
	Proofing
};

class LanguageSelector : public QDialog {
	Q_OBJECT

public:
	LanguageSelector(QMainWindow* parent = nullptr, CallType callType = None);
	~LanguageSelector();

private slots:
	[[maybe_unused]] void on_buttonBox_accepted();
	[[maybe_unused]] void on_buttonBox_rejected();
	void reject() override;

private:
	Ui::LanguageSelector* ui;
	Installer* installer;
	CallType callType;
	QVector<QCheckBox*> checkBoxLangs;
	void widgetPopulator(QScrollArea* scrollArea);
};

#endif//LANGUAGESELECTOR_HPP
