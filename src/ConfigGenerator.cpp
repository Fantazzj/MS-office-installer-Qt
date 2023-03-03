#include "ConfigGenerator.hpp"

ConfigGenerator::ConfigGenerator(Ui::Installer* ui) {
	_ui = ui;

	apps.append(_ui->checkBoxWord);
	apps.append(_ui->checkBoxPowerPoint);
	apps.append(_ui->checkBoxExcel);
	apps.append(_ui->checkBoxAccess);
	apps.append(_ui->checkBoxPublisher);
	apps.append(_ui->checkBoxOutlook);
	apps.append(_ui->checkBoxTeams);
	apps.append(_ui->checkBoxOneDrive);
	apps.append(_ui->checkBoxOneNote);
	apps.append(_ui->checkBoxGroove);
	apps.append(_ui->checkBoxInfoPath);
	apps.append(_ui->checkBoxLync);
	apps.append(_ui->checkBoxProject);
	apps.append(_ui->checkBoxSharePointDesigner);
}

ConfigGenerator::~ConfigGenerator() {
	if(configFile->isOpen()) configFile->close();
}

void ConfigGenerator::createFile(QString nameFile) {
	configFile = new QFile(nameFile);
	configFile->open(QIODevice::WriteOnly | QIODevice::Text);
	configXml = new QXmlStreamWriter(configFile);

	configXml->setAutoFormatting(true);

	//1 O
	configXml->writeStartElement("Configuration");

	//2 O
	_writeAddElement();

	//3 O
	_writeProductOfficeElement();
	_writeOfficeLangsElements();
	_writeExludeAppElements();
	//3 C
	configXml->writeEndElement();

	//3 O
	_writeProductProofingElement();
	_writeProofingLangsElements();
	//3 C
	configXml->writeEndElement();

	//3 O
	configXml->writeEndElement();
	configXml->writeEndElement();
	configXml->writeEndElement();

	//2 C
	configXml->writeEndElement();

	//1 C
	configXml->writeEndElement();

	configFile->close();
}

void ConfigGenerator::_writeAddElement() {
	QString version = "64";
	QString channel = "Current";

	version = _ui->comboBoxVersion->currentText().remove(" bit");
	channel = _ui->comboBoxRelease->currentText();

	configXml->writeStartElement("Add");
	configXml->writeAttribute("OfficeClientEdition", version);
	configXml->writeAttribute("Channel", channel);

}

void ConfigGenerator::_writeProductOfficeElement() {
	configXml->writeStartElement("Product");
}

void ConfigGenerator::_writeProductProofingElement() {
	configXml->writeStartElement("Product");
}

void ConfigGenerator::_writeOfficeLangsElements() {
	configXml->writeStartElement("Language");
	configXml->writeEndElement();
}

void ConfigGenerator::_writeProofingLangsElements() {
	configXml->writeStartElement("Language");
	configXml->writeEndElement();
}

void ConfigGenerator::_writeExludeAppElements() {
	for(auto& A: apps)
		if(!A->isChecked()) {
			configXml->writeStartElement("EXcludeApp");
			configXml->writeAttribute("ID", A->accessibleName());
			configXml->writeEndElement();
		}
}

void ConfigGenerator::_writeUpdatesElement() {
	configXml->writeStartElement("Updates");
	if(_ui->checkBoxUpdates->isChecked())
		configXml->writeAttribute("Enabled", "TRUE");
	else
		configXml->writeAttribute("Enabled", "FALSE");
}
