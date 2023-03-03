#include "ConfigGenerator.hpp"

ConfigGenerator::ConfigGenerator(Ui::Installer ui) {
	configFile = new QFile("config.xml");
	configFile->open(QIODevice::WriteOnly | QIODevice::Text);
	configXml = new QXmlStreamWriter(configFile);
	_ui = ui;
}
