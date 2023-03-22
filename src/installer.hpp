#ifndef INSTALLER_HPP
#define INSTALLER_HPP

#include <QDesktopServices>
#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QProgressDialog>
#include <QThread>

#include "ConfigGenerator.hpp"
#include "DataModel.hpp"
#include "languageSelector.hpp"
#include "OfficeDeploymentTool.hpp"

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
	QJsonObject getJsonObj();
	Model installerData;

private slots:
	[[maybe_unused]] void on_pushButtonExport_clicked();
	[[maybe_unused]] void on_pushButtonInstall_clicked();
	[[maybe_unused]] void on_toolButtonOfficeSetup_clicked();
	[[maybe_unused]] void on_pushButtonPrdLang_clicked();
	[[maybe_unused]] void on_pushButtonPrfLng_clicked();
	[[maybe_unused]] void updateData();
	[[maybe_unused]] void on_toolButtonDeployInfo_clicked();

private:
	Ui::Installer* ui;
	QList<QCheckBox*> checkBoxApps;
	QJsonObject jsonObj;
	void comboBoxPopulator(QComboBox* comboBox, const QString& key);
};
#endif//INSTALLER_HPP
