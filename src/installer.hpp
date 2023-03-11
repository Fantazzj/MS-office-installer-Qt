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
	[[maybe_unused]] void on_pushButtonExport_clicked();
	[[maybe_unused]] void on_pushButtonDownload_clicked();
	[[maybe_unused]] void on_pushButtonInstall_clicked();
	[[maybe_unused]] void on_pushButtonDownloadAndInstall_clicked();
	[[maybe_unused]] void on_toolButtonOfficeSetup_clicked();
	[[maybe_unused]] void on_pushButtonPrdLang_clicked();
	[[maybe_unused]] void on_pushButtonPrfLng_clicked();

private:
	Ui::Installer* ui;
	OfficeDeploymentTool* office;
	QJsonObject jsonObj;
	void comboBoxPopulator(QComboBox* comboBox, const QString& key);
};
#endif//INSTALLER_HPP
