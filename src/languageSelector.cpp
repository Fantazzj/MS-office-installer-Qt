#include "languageSelector.hpp"
#include "ui_languageSelector.h"

languageSelector::languageSelector(QMainWindow* parent, Ui::Installer* installerUi) :
	QDialog(parent, Qt::Dialog), ui(new Ui::languageSelector) {
	ui->setupUi(this);
	this->installerUi = installerUi;
	qDebug() << "langUi created";
}

languageSelector::~languageSelector() {
	qDebug() << "langUi destroyed";
	qDebug() << SEPARATOR;
	delete ui;
}

void languageSelector::on_buttonBox_accepted() {
	qDebug() << "confirm";
	delete this;
}

void languageSelector::on_buttonBox_rejected() {
	reject();
}
void languageSelector::reject() {
	qDebug() << "cancel";
	delete this;
}
