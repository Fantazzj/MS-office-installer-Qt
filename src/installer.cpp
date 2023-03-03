#include "installer.hpp"
#include "ui_installer.h"

Installer::Installer(QWidget* parent) :
	QMainWindow(parent), ui(new Ui::Installer) {
	ui->setupUi(this);

	ui->checkBoxWord->setChecked(true);
	ui->checkBoxPowerPoint->setChecked(true);
	ui->checkBoxExcel->setChecked(true);

	office = new OfficeDeploymentTool();
	xml = new ConfigGenerator(ui);
}

Installer::~Installer() {
	delete ui;
}

void Installer::on_pushButtonExport_clicked() {

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
