#include "installer.hpp"

#include "ui_installer.h"

Installer::Installer(QWidget* parent) :
	QMainWindow(parent), ui(new Ui::Installer) {
	ui->setupUi(this);

	if(!QFile("setup.exe").exists()) {
		QMessageBox::warning(this, tr("Missing setup.exe"),
							 tr("There is no office's setup.exe, so you cannot install or download, only export configuration"));
		ui->pushButtonDownload->setDisabled(true);
		ui->pushButtonInstall->setDisabled(true);
		ui->pushButtonDownloadAndInstall->setDisabled(true);
	}

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

	office = new OfficeDeploymentTool();
}

Installer::~Installer() {
	delete ui;
}

[[maybe_unused]] void Installer::on_pushButtonExport_clicked() {
	auto fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
												 "config.xml",
												 tr("Configuration file (*.xml)"));
	if(!fileName.isEmpty()) {
		auto config = ConfigGenerator(this, fileName);
		config.createFile();
	}
}

void Installer::on_pushButtonDownload_clicked() {
	office->download();
}

void Installer::on_pushButtonInstall_clicked() {
	office->install();
}

[[maybe_unused]] void Installer::on_pushButtonDownloadAndInstall_clicked() {
	on_pushButtonDownload_clicked();
	on_pushButtonInstall_clicked();
}

[[maybe_unused]] void Installer::on_toolButtonOfficeSetup_clicked() {
	auto dirName = QFileDialog::getExistingDirectory(this, tr("Office extracted files"));
	ui->lineEditOfficeSetup->setText(dirName);
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

void Installer::setPrdLanguages(QStringList productLangs) {
	this->productLangs = productLangs;
}

void Installer::setPrfLanguages(QStringList proofingLangs) {
	this->proofingLangs = proofingLangs;
}

QJsonObject Installer::getJsonObj() {
	return jsonObj;
}
Ui::Installer* Installer::getUi() {
	return ui;
}
