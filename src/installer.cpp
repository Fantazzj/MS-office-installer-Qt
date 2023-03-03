#include "installer.hpp"
#include "ui_installer.h"

Installer::Installer(QWidget* parent) :
	QMainWindow(parent), ui(new Ui::Installer) {

	ui->setupUi(this);

	ui->checkBoxWord->setChecked(true);
	ui->checkBoxPowerPoint->setChecked(true);
	ui->checkBoxExcel->setChecked(true);

	ui->comboBoxVersion->addItem("64 bit");
	ui->comboBoxVersion->addItem("32 bit");

	ui->comboBoxRelease->addItem("Current");
	ui->comboBoxRelease->addItem("Stable??");

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
