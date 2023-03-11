#include "languageSelector.hpp"
#include "ui_languageSelector.h"

languageSelector::languageSelector(QMainWindow* parent) :
	QDialog(parent, Qt::Dialog), ui(new Ui::languageSelector) {
	ui->setupUi(this);
	installer = dynamic_cast<Installer*>(parent);
	qDebug() << "langUi created";
}

languageSelector::~languageSelector() {
	qDebug() << "langUi destroyed";
	qDebug() << SEPARATOR;
	delete ui;
}

[[maybe_unused]] void languageSelector::on_buttonBox_accepted() {
	qDebug() << "confirm";
	delete this;
}

[[maybe_unused]] void languageSelector::on_buttonBox_rejected() {
	reject();
}
void languageSelector::reject() {
	qDebug() << "cancel";
	delete this;
}
