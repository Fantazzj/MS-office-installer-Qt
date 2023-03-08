#ifndef CONFIGGENERATOR_HPP
#define CONFIGGENERATOR_HPP

#include "ui_installer.h"
#include <QStandardItemModel>
#include <QFile>
#include <QXmlStreamWriter>
#include <QVector>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

class ConfigGenerator {
public:
	ConfigGenerator(Ui::Installer* ui);
	~ConfigGenerator();
	void createFile(QString nameFile);

private:
	QFile* configFile;
	QXmlStreamWriter* configXml;
	QJsonObject _jsonObj;
	Ui::Installer* _ui;
	QVector<QCheckBox*> apps;
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
