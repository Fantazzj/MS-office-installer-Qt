#include "Installer.hpp"
#include "ui_installer.h"

Installer::Installer(QWidget* parent) :
    QMainWindow(parent), ui(new Ui::Installer) {
    ui->setupUi(this);

    ui->checkBoxWord->setChecked(true);
    ui->checkBoxPowerPoint->setChecked(true);
    ui->checkBoxExcel->setChecked(true);

    office = OfficeDeploymentTool();
    xml = ConfigGenerator();
}

Installer::~Installer() {
    delete ui;
}

void Installer::on_startInstall_clicked() {

}
