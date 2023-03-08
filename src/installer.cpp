#include "installer.hpp"
#include "ui_installer.h"

Installer::Installer(QWidget* parent) :
	QMainWindow(parent), ui(new Ui::Installer) {
	ui->setupUi(this);

	if(!QFile("setup.exe").exists()) {
		ui->pushButtonDownload->setDisabled(true);
		ui->pushButtonInstall->setDisabled(true);
		ui->pushButtonDownloadAndInstall->setDisabled(true);
	}

	office = new OfficeDeploymentTool();
	config = new ConfigGenerator(ui);
}

Installer::~Installer() {
	delete ui;
}

void Installer::on_pushButtonExport_clicked() {
	config->createFile("config.xml");
}

void Installer::on_pushButtonDownload_clicked() {
	office->download();
}

void Installer::on_pushButtonInstall_clicked() {
	office->install();
}

void Installer::on_pushButtonDownloadAndInstall_clicked() {
	on_pushButtonDownload_clicked();
	on_pushButtonInstall_clicked();
}

void Installer::on_toolButtonOfficeSetup_clicked() {
}

void Installer::on_pushButtonPrdLang_clicked() {
	auto* langUi = new languageSelector(nullptr, ui);
	ui->centralwidget->setDisabled(true);
	langUi->show();
}

void Installer::on_pushButtonPrfLng_clicked() {
	auto* langUi = new languageSelector(nullptr, ui);
	ui->centralwidget->setDisabled(true);
	langUi->show();
}
