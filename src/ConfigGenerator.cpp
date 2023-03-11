#include "ConfigGenerator.hpp"

ConfigGenerator::ConfigGenerator(Ui::Installer* ui) {
	installerUi = ui;

	checkBoxApps.append(installerUi->checkBoxWord);
	checkBoxApps.append(installerUi->checkBoxPowerPoint);
	checkBoxApps.append(installerUi->checkBoxExcel);
	checkBoxApps.append(installerUi->checkBoxAccess);
	checkBoxApps.append(installerUi->checkBoxPublisher);
	checkBoxApps.append(installerUi->checkBoxOutlook);
	checkBoxApps.append(installerUi->checkBoxTeams);
	checkBoxApps.append(installerUi->checkBoxOneDrive);
	checkBoxApps.append(installerUi->checkBoxOneNote);
	checkBoxApps.append(installerUi->checkBoxGroove);
	checkBoxApps.append(installerUi->checkBoxInfoPath);
	checkBoxApps.append(installerUi->checkBoxLync);
	checkBoxApps.append(installerUi->checkBoxProject);
	checkBoxApps.append(installerUi->checkBoxSharePointDesigner);
}

ConfigGenerator::~ConfigGenerator() {
	if(configFile->isOpen()) configFile->close();
}

void ConfigGenerator::createFile(QString nameFile) {
	configFile = new QFile(nameFile);
	configFile->open(QIODevice::WriteOnly | QIODevice::Text);
	configXml = new QXmlStreamWriter(configFile);

	configXml->setAutoFormatting(true);

	configXml->writeStartElement("Configuration");

	_writeAddElement();//Add

	_writeProductOfficeElement();//Product
	_writeOfficeLangsElements(); //Language
	_writeExcludeAppElements();	 //ExcludeApp
	configXml->writeEndElement();//Product

	_writeProductProofingElement();//Product
	_writeProofingLangsElements(); //Language
	configXml->writeEndElement();  //Product

	configXml->writeEndElement();//Add

	_writeUpdatesElement();		 //Updates
	configXml->writeEndElement();//Updates

	configXml->writeEndElement();//Configuration

	configFile->close();
}

void ConfigGenerator::_writeAddElement() {
	QString version = "64";
	QString channel = "Current";

	version = installerUi->comboBoxVersion->currentData().toString();
	channel = installerUi->comboBoxRelease->currentText();

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
	configXml->writeEndElement();//Language
}

void ConfigGenerator::_writeProofingLangsElements() {
	configXml->writeStartElement("Language");
	configXml->writeEndElement();//Language
}

void ConfigGenerator::_writeExcludeAppElements() {
	for(auto& A: checkBoxApps)
		if(!A->isChecked()) {
			configXml->writeStartElement("ExcludeApp");
			configXml->writeAttribute("ID", A->objectName().remove("checkBox"));
			configXml->writeEndElement();//ExcludeApp
		}
}

void ConfigGenerator::_writeUpdatesElement() {
	configXml->writeStartElement("Updates");
	if(installerUi->checkBoxUpdates->isChecked())
		configXml->writeAttribute("Enabled", "TRUE");
	else
		configXml->writeAttribute("Enabled", "FALSE");
}
