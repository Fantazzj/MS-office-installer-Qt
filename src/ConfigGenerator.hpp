#ifndef CONFIGGENERATOR_HPP
#define CONFIGGENERATOR_HPP

#include "ui_installer.h"
#include <QFile>
#include <QXmlStreamWriter>
#include <QVector>

class ConfigGenerator {
public:
	ConfigGenerator(Ui::Installer* ui);
	~ConfigGenerator();
	void createFile(QString nameFile);

private:
	QFile* configFile;
	QXmlStreamWriter* configXml;
	Ui::Installer* _ui;
	QVector<QCheckBox*> apps;
	void _writeAddElement();
	void _writeProductOfficeElement();
	void _writeProductProofingElement();
	void _writeOfficeLangsElements();
	void _writeProofingLangsElements();
	void _writeExcludeAppElements();
	void _writeUpdatesElement();
};

#endif//CONFIGGENERATOR_HPP
