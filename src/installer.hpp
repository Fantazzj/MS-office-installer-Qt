#ifndef INSTALLER_HPP
#define INSTALLER_HPP

#include "ConfigGenerator.hpp"
#include "OfficeDeploymentTool.hpp"
#include "languageSelector.hpp"
#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
	class Installer;
}
QT_END_NAMESPACE

class Installer : public QMainWindow {
	Q_OBJECT

public:
	Installer(QWidget* parent = nullptr);
	~Installer();

private slots:
	void on_pushButtonExport_clicked();
	void on_pushButtonDownload_clicked();
	void on_pushButtonInstall_clicked();
	void on_pushButtonDownloadAndInstall_clicked();
	void on_toolButtonOfficeSetup_clicked();
	void on_pushButtonPrdLang_clicked();
	void on_pushButtonPrfLng_clicked();

private:
	Ui::Installer* ui;
	languageSelector* langUi;
	ConfigGenerator* config;
	OfficeDeploymentTool* office;
};
#endif//INSTALLER_HPP
