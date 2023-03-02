#ifndef CONFIGGENERATOR_HPP
#define CONFIGGENERATOR_HPP

#include <QXmlStreamWriter>
#include <QFile>

class ConfigGenerator {
public:
    ConfigGenerator();
private:
    QFile* configFile;
    QXmlStreamWriter* configXml;
};

#endif// CONFIGGENERATOR_HPP
