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

#include "DataModel.hpp"
#include "installer.hpp"
#include "ui_installer.h"

class Installer;

class ConfigGenerator {
public:
	ConfigGenerator(Model installerData, const QString& fileName);
	~ConfigGenerator();
	void createFile();

private:
	QFile* configFile;
	QXmlStreamWriter* configXml;
	Model installerData;
	void writeAddElement();
	void writeProductOfficeElement();
	void writeProductProofingElement();
	void writeOfficeLangsElements();
	void writeProofingLangsElements();
	void writeExcludeAppElements();
	void writeUpdatesElement();
	void writeSaveFileType();
};

#endif//CONFIGGENERATOR_HPP
