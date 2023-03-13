#ifndef CONFIGGENERATOR_HPP
#define CONFIGGENERATOR_HPP

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QStandardItemModel>
#include <QVector>
#include <QXmlStreamWriter>

#include "installer.hpp"
#include "ui_installer.h"

class ConfigGenerator {
public:
	ConfigGenerator(Ui::Installer* ui, const QString& fileName);
	~ConfigGenerator();
	void createFile();

private:
	QFile* configFile;
	QXmlStreamWriter* configXml;
	Ui::Installer* installerUi;
	QVector<QCheckBox*> checkBoxApps;
	void _writeAddElement();
	void _writeProductOfficeElement();
	void _writeProductProofingElement();
	void _writeOfficeLangsElements();
	void _writeProofingLangsElements();
	void _writeExcludeAppElements();
	void _writeUpdatesElement();
};

#endif//CONFIGGENERATOR_HPP
