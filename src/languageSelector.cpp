#include "languageSelector.hpp"
#include "ui_languageSelector.h"

languageSelector::languageSelector(QDialog* parent, Ui::Installer* installerUi) :
	QDialog(parent), ui(new Ui::languageSelector) {
	ui->setupUi(this);
	installerUi = installerUi;
	qDebug() << "langUi created";
}

languageSelector::~languageSelector() {
	qDebug() << "langUi destroyed";
	qDebug() << SEPARATOR;
	delete ui;
}

void languageSelector::on_buttonBox_accepted() {
	installerUi->centralwidget->setEnabled(true);
	qDebug() << "confirm";
	delete this;
}

void languageSelector::on_buttonBox_rejected() {
	reject();
}
void languageSelector::reject() {
	installerUi->centralwidget->setEnabled(true);
	qDebug() << "cancel";
	delete this;
}
