#include "languageSelector.hpp"
#include "ui_languageSelector.h"

languageSelector::languageSelector(QMainWindow* parent, CallType callType) :
	QDialog(parent, Qt::Dialog), ui(new Ui::languageSelector) {
	ui->setupUi(this);
	installer = dynamic_cast<Installer*>(parent);
	this->callType = callType;

	widgetPopulator(ui->scrollArea);

	qDebug() << "langUi created";
	qDebug() << "call type:" << callType;
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

void languageSelector::widgetPopulator(QScrollArea* scrollArea) {
	auto jsonObj = installer->getJsonObj();
	auto languages = jsonObj.value("languages").toArray();

	QVBoxLayout* layout = new QVBoxLayout();
	for(auto l: languages) {
		qDebug() << l.toArray().at(0) << l.toArray().at(1);
		QCheckBox* checkBox = new QCheckBox(l.toArray().at(0).toString());
		layout->addWidget(checkBox);
	}

	scrollArea->setLayout(layout);
}
