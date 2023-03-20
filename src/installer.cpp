#include "installer.hpp"

#include "ui_installer.h"

Installer::Installer(QWidget* parent) :
	QMainWindow(parent), ui(new Ui::Installer) {
	ui->setupUi(this);

#ifdef DEBUG
	auto jsonFile = QFile("../res/contents.json");
#else
	auto jsonFile = QFile("contents.json");
#endif

	jsonFile.open(QIODevice::ReadOnly | QIODevice::Text);
	QString dummy = jsonFile.readAll();
	auto jsonDoc = QJsonDocument::fromJson(dummy.toUtf8());
	jsonFile.close();
	jsonObj = jsonDoc.object();

	comboBoxPopulator(ui->comboBoxVersion, "versions");
	comboBoxPopulator(ui->comboBoxProduct, "product");
	comboBoxPopulator(ui->comboBoxRelease, "releaseChannel");
}

Installer::~Installer() {
	delete ui;
}

[[maybe_unused]] void Installer::on_pushButtonExport_clicked() {
	if(productLangs.isEmpty()) {
		auto reply = QMessageBox::question(this,
										   tr("Missing languages"),
										   tr("You did not choose any language for product, load it from your os language?"));

		if(reply == QMessageBox::Yes) {
			qDebug() << QLocale::system().uiLanguages().at(0);
			productLangs.append(QLocale::system().uiLanguages().at(0).toLower());
		} else return;
	}

	auto fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
												 "config.xml",
												 tr("Configuration file (*.xml)"));
	if(fileName.isEmpty()) return;

	auto config = ConfigGenerator(this, fileName);
	config.createFile();
}

[[maybe_unused]] void Installer::on_pushButtonInstall_clicked() {
	if(productLangs.isEmpty()) {
		auto reply = QMessageBox::question(this,
										   tr("Missing languages"),
										   tr("You did not choose any language for product, load it from your os language?"));

		if(reply == QMessageBox::Yes) {
			qDebug() << QLocale::system().uiLanguages().at(0);
			productLangs.append(QLocale::system().uiLanguages().at(0).toLower());
		} else return;
	}

	QString setupFile = ui->lineEditOfficeSetup->text();
	QString configFile = setupFile;
	configFile.replace("setup.exe", "config.xml");

	qDebug() << setupFile;
	qDebug() << configFile;

	auto config = ConfigGenerator(this, configFile);
	config.createFile();

	auto office = OfficeDeploymentTool(setupFile, configFile);
	office.install();
}

[[maybe_unused]] void Installer::on_toolButtonOfficeSetup_clicked() {
	auto setupFile = QFileDialog::getOpenFileName(this, tr("Office setup files"));

	if(setupFile.endsWith("setup.exe")) {
		ui->pushButtonInstall->setEnabled(true);
	} else
		QMessageBox::warning(this, tr("Missing setup.exe"),
							 tr("There is no office's setup.exe, so you cannot install or download, only export configuration"));

	ui->lineEditOfficeSetup->setText(setupFile);
}

[[maybe_unused]] void Installer::on_pushButtonPrdLang_clicked() {
	auto langUi = new languageSelector(this, CallType::Product);
	langUi->setWindowModality(Qt::WindowModality::WindowModal);
	langUi->show();
}

[[maybe_unused]] void Installer::on_pushButtonPrfLng_clicked() {
	auto* langUi = new languageSelector(this, CallType::Proofing);
	langUi->setWindowModality(Qt::WindowModality::WindowModal);
	langUi->show();
}

void Installer::comboBoxPopulator(QComboBox* comboBox, const QString& key) {
	auto versions = jsonObj.value(key).toArray();
	qDebug() << versions;
	for(QJsonValueRef A: versions) {
		qDebug() << A.toArray().at(0) << A.toArray().at(1);
		comboBox->addItem(A.toArray().at(0).toString(), A.toArray().at(1).toString());
	}
	qDebug() << SEPARATOR;
}

QJsonObject Installer::getJsonObj() {
	return jsonObj;
}

Ui::Installer* Installer::getUi() {
	return ui;
}
