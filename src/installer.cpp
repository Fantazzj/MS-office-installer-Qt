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

	checkBoxApps.append(ui->checkBoxWord);
	checkBoxApps.append(ui->checkBoxPowerPoint);
	checkBoxApps.append(ui->checkBoxExcel);
	checkBoxApps.append(ui->checkBoxAccess);
	checkBoxApps.append(ui->checkBoxPublisher);
	checkBoxApps.append(ui->checkBoxOutlook);
	checkBoxApps.append(ui->checkBoxTeams);
	checkBoxApps.append(ui->checkBoxOneDrive);
	checkBoxApps.append(ui->checkBoxOneNote);
	checkBoxApps.append(ui->checkBoxGroove);
	checkBoxApps.append(ui->checkBoxInfoPath);
	checkBoxApps.append(ui->checkBoxLync);
	checkBoxApps.append(ui->checkBoxProject);
	checkBoxApps.append(ui->checkBoxSharePointDesigner);

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
	qDebug() << "installer destroyed";
	qDebug() << SEPARATOR;
}

[[maybe_unused]] void Installer::on_pushButtonExport_clicked() {
	if(installerData.productLangs.isEmpty()) {
		auto reply = QMessageBox::question(this,
										   tr("Missing languages"),
										   tr("You did not choose any language for product, load it from your os language?"));

		if(reply == QMessageBox::Yes) {
			qDebug() << QLocale::system().uiLanguages().at(0);
			installerData.productLangs.append(QLocale::system().uiLanguages().at(0).toLower());
		} else return;
	}

	auto fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
												 "config.xml",
												 tr("Configuration file (*.xml)"));
	if(fileName.isEmpty()) return;

	auto config = ConfigGenerator(installerData, fileName);
	config.createFile();
}

[[maybe_unused]] void Installer::on_pushButtonInstall_clicked() {
	if(installerData.productLangs.isEmpty()) {
		auto reply = QMessageBox::question(this,
										   tr("Missing languages"),
										   tr("You did not choose any language for product, load it from your os language?"));

		if(reply == QMessageBox::Yes) {
			qDebug() << QLocale::system().uiLanguages().at(0);
			installerData.productLangs.append(QLocale::system().uiLanguages().at(0).toLower());
		} else return;
	}

	auto config = ConfigGenerator(installerData, installerData.setupDir + "/config.xml");
	config.createFile();

	auto office = OfficeDeploymentTool(installerData);
	//office.install();
}

[[maybe_unused]] void Installer::on_toolButtonOfficeSetup_clicked() {
	auto setupDirectory = QFileDialog::getExistingDirectory(this, tr("Office setup files"));

	if(setupDirectory.isEmpty()) return;

	if(!QFile(setupDirectory + "/setup.exe").exists()) {
		QMessageBox::warning(this, tr("Missing setup.exe"),
							 tr("There is no office's setup.exe, so you cannot install or download, only export configuration"));
		ui->pushButtonInstall->setDisabled(true);
		ui->lineEditOfficeSetup->setText("");
	} else {
		ui->lineEditOfficeSetup->setText(setupDirectory);
		ui->pushButtonInstall->setEnabled(true);
	}
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

[[maybe_unused]] void Installer::updateData() {
	installerData.exPrograms.clear();
	for(auto C: checkBoxApps) {
		if(!C->isChecked()) installerData.exPrograms.append(C->text());
	}

	installerData.version = ui->comboBoxVersion->currentData().toString();
	installerData.product = ui->comboBoxProduct->currentData().toString();
	installerData.release = ui->comboBoxRelease->currentData().toString();

	if(ui->radioButtonOpenXml->isChecked())
		installerData.saveType = SaveType::OpenXml;
	else if(ui->radioButtonOpenDocument->isChecked())
		installerData.saveType = SaveType::OpenDoc;
	else
		installerData.saveType = SaveType::NotNow;

	installerData.setupDir = ui->lineEditOfficeSetup->text();
	installerData.updates = ui->checkBoxUpdates->isChecked();

	qDebug() << "data updated:";
	qDebug() << installerData.exPrograms;
	qDebug() << installerData.productLangs;
	qDebug() << installerData.proofingLangs;
	qDebug() << installerData.version;
	qDebug() << installerData.product;
	qDebug() << installerData.release;
	qDebug() << installerData.setupDir;
	qDebug() << installerData.saveType;
	qDebug() << installerData.updates;
	qDebug() << SEPARATOR;
}

[[maybe_unused]] void Installer::on_toolButtonDeployInfo_clicked() {
	QDesktopServices::openUrl(QUrl("https://www.microsoft.com/en-us/download/details.aspx?id=49117", QUrl::TolerantMode));
}
