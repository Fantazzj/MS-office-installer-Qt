#include "ConfigGenerator.hpp"

ConfigGenerator::ConfigGenerator() {
    configFile = new QFile("config.xml");
    configFile->open(QIODevice::WriteOnly | QIODevice::Text);
    configXml = new QXmlStreamWriter(configFile);
}