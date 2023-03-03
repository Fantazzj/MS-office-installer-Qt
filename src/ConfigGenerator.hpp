#ifndef CONFIGGENERATOR_HPP
#define CONFIGGENERATOR_HPP

#include "ui_installer.h"
#include <QFile>
#include <QXmlStreamWriter>

class ConfigGenerator {
public:
	ConfigGenerator(Ui::Installer ui);

private:
	QFile* configFile;
	QXmlStreamWriter* configXml;
	Ui::Installer _ui;
};

#endif// CONFIGGENERATOR_HPP
