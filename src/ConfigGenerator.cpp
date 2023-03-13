#include "ConfigGenerator.hpp"

ConfigGenerator::ConfigGenerator(Installer* installer, const QString& fileName) {
	this->installer = installer;
	installerUi = installer->getUi();

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

	configFile = new QFile(fileName);
	configFile->open(QIODevice::WriteOnly | QIODevice::Text);
	configXml = new QXmlStreamWriter(configFile);
}

ConfigGenerator::~ConfigGenerator() {
	if(configFile != nullptr && configFile->isOpen()) configFile->close();
}

void ConfigGenerator::createFile() {
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
	QString version = installerUi->comboBoxVersion->currentData().toString();
	QString channel = installerUi->comboBoxRelease->currentData().toString();

	configXml->writeStartElement("Add");
	configXml->writeAttribute("OfficeClientEdition", version);
	configXml->writeAttribute("Channel", channel);
}

void ConfigGenerator::_writeProductOfficeElement() {
	auto release = installerUi->comboBoxProduct->currentData().toString();

	configXml->writeStartElement("Product");
	configXml->writeAttribute("ID", release);
}

void ConfigGenerator::_writeProductProofingElement() {
	configXml->writeStartElement("Product");
	configXml->writeAttribute("ID", "ProofingTools");
}

void ConfigGenerator::_writeOfficeLangsElements() {
	for(auto L: installer->productLangs) {
		configXml->writeStartElement("Language");
		configXml->writeAttribute("ID", L);
		configXml->writeEndElement();//Language
	}
}

void ConfigGenerator::_writeProofingLangsElements() {
	for(auto L: installer->proofingLangs) {
		configXml->writeStartElement("Language");
		configXml->writeAttribute("ID", L);
		configXml->writeEndElement();//Language
	}
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
