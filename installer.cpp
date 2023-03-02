#include "installer.h"
#include "ui_installer.h"

Installer::Installer(QWidget* parent) :
    QMainWindow(parent), ui(new Ui::Installer) {
    ui->setupUi(this);

    ui->checkBoxWord->setChecked(true);
    ui->checkBoxPowerPoint->setChecked(true);
    ui->checkBoxExcel->setChecked(true);

    OfficeDeploymentTool office = OfficeDeploymentTool();
}

Installer::~Installer() {
    delete ui;
}
