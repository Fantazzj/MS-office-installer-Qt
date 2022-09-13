#include "installer.h"
#include "ui_installer.h"

Installer::Installer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Installer)
{
    ui->setupUi(this);

}

Installer::~Installer()
{
    delete ui;
}

