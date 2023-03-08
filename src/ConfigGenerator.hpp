#ifndef CONFIGGENERATOR_HPP
#define CONFIGGENERATOR_HPP

#include "ui_installer.h"
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QStandardItemModel>
#include <QVector>
#include <QXmlStreamWriter>

class ConfigGenerator {
public:
	ConfigGenerator(Ui::Installer* ui);
	~ConfigGenerator();
	void createFile(QString nameFile);

private:
	QFile* configFile;
	QXmlStreamWriter* configXml;
	QJsonObject jsonObj;
	Ui::Installer* installerUi;
	QVector<QCheckBox*> checkBoxApps;
	void _writeAddElement();
	void _writeProductOfficeElement();
	void _writeProductProofingElement();
	void _writeOfficeLangsElements();
	void _writeProofingLangsElements();
	void _writeExcludeAppElements();
	void _writeUpdatesElement();
	void _comboBoxPopulator(QComboBox* comboBox, QString key);
};

#endif//CONFIGGENERATOR_HPP
