#include "languageSelector.hpp"
#include "ui_languageSelector.h"

languageSelector::languageSelector(QMainWindow* parent, CallType callType) :
	QDialog(parent, Qt::Dialog), ui(new Ui::languageSelector) {
	ui->setupUi(this);
	installer = dynamic_cast<Installer*>(parent);
	this->callType = callType;
	qDebug() << "langUi created";
}

languageSelector::~languageSelector() {
	qDebug() << "langUi destroyed";
	qDebug() << SEPARATOR;
	delete ui;
}

[[maybe_unused]] void languageSelector::on_buttonBox_accepted() {
	qDebug() << "confirm";
	if(callType == CallType::Product)
		;
	else if(callType == CallType::Proofing)
		;
	delete this;
}

[[maybe_unused]] void languageSelector::on_buttonBox_rejected() {
	reject();
}
void languageSelector::reject() {
	qDebug() << "cancel";
	delete this;
}
