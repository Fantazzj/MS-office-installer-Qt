#include "ConfigGenerator.hpp"

ConfigGenerator::ConfigGenerator(Model installerData, const QString& fileName) {
	//this->installer = installer;
	//installerUi = installer->getUi();

	this->installerData = installerData;

	/*checkBoxApps.append(installerUi->checkBoxWord);
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
	checkBoxApps.append(installerUi->checkBoxSharePointDesigner);*/

	configFile = new QFile(fileName);
	configFile->open(QIODevice::WriteOnly | QIODevice::Text);
	configXml = new QXmlStreamWriter(configFile);
}

ConfigGenerator::~ConfigGenerator() {
	if(configFile != nullptr && configFile->isOpen()) configFile->close();
	qDebug() << "ConfigGenerator destroyed";
	qDebug() << SEPARATOR;
}

void ConfigGenerator::createFile() {
	configXml->setAutoFormatting(true);

	configXml->writeStartElement("Configuration");

	writeAddElement();//Add

	writeProductOfficeElement(); //Product
	writeOfficeLangsElements();	 //Language
	writeExcludeAppElements();	 //ExcludeApp
	configXml->writeEndElement();//Product

	writeProductProofingElement();//Product
	writeProofingLangsElements(); //Language
	configXml->writeEndElement(); //Product

	configXml->writeEndElement();//Add

	writeUpdatesElement();		 //Updates
	configXml->writeEndElement();//Updates

	configXml->writeStartElement("RemoveMSI");
	configXml->writeEndElement();//RemoveMSI

	configXml->writeStartElement("AppSettings");
	writeSaveFileType();
	configXml->writeEndElement();//AppSettings

	configXml->writeEndElement();//Configuration

	configFile->close();
}

void ConfigGenerator::writeAddElement() {
	//QString version = installerUi->comboBoxVersion->currentData().toString();
	//QString channel = installerUi->comboBoxRelease->currentData().toString();

	configXml->writeStartElement("Add");
	configXml->writeAttribute("OfficeClientEdition", installerData.version);
	configXml->writeAttribute("Channel", installerData.release);
}

void ConfigGenerator::writeProductOfficeElement() {
	//auto release = installerUi->comboBoxProduct->currentData().toString();

	configXml->writeStartElement("Product");
	configXml->writeAttribute("ID", installerData.product);
}

void ConfigGenerator::writeProductProofingElement() {
	configXml->writeStartElement("Product");
	configXml->writeAttribute("ID", "ProofingTools");
}

void ConfigGenerator::writeOfficeLangsElements() {
	for(auto& L: installerData.productLangs) {
		configXml->writeStartElement("Language");
		configXml->writeAttribute("ID", L);
		configXml->writeEndElement();//Language
	}
}

void ConfigGenerator::writeProofingLangsElements() {
	for(auto& L: installerData.proofingLangs) {
		configXml->writeStartElement("Language");
		configXml->writeAttribute("ID", L);
		configXml->writeEndElement();//Language
	}
}

void ConfigGenerator::writeExcludeAppElements() {
	for(auto& P: installerData.exPrograms) {
		configXml->writeStartElement("ExcludeApp");
		configXml->writeAttribute("ID", P);
		configXml->writeEndElement();//ExcludeApp
	}
}

void ConfigGenerator::writeUpdatesElement() {
	configXml->writeStartElement("Updates");
	if(installerData.updates)
		configXml->writeAttribute("Enabled", "TRUE");
	else
		configXml->writeAttribute("Enabled", "FALSE");
}

void ConfigGenerator::writeSaveFileType() {
	if(installerData.saveType == SaveType::NotNow)
		return;

	if(installerData.saveType == SaveType::OpenXml) {
		//word
		configXml->writeStartElement("User");
		configXml->writeAttribute("Key", R"(software\microsoft\office\16.0\word\options)");
		configXml->writeAttribute("Name", "defaultformat");
		configXml->writeAttribute("Value", "");
		configXml->writeAttribute("Type", "REG_SZ");
		configXml->writeAttribute("App", "word16");
		configXml->writeAttribute("Id", "L_SaveWordfilesas");
		configXml->writeEndElement();
		//powerpoint
		configXml->writeStartElement("User");
		configXml->writeAttribute("Key", R"(software\microsoft\office\16.0\powerpoint\options)");
		configXml->writeAttribute("Name", "defaultformat");
		configXml->writeAttribute("Value", "27");
		configXml->writeAttribute("Type", "REG_DWORD");
		configXml->writeAttribute("App", "ppt16");
		configXml->writeAttribute("Id", "L_SavePowerPointfilesas");
		configXml->writeEndElement();
		//excel
		configXml->writeStartElement("User");
		configXml->writeAttribute("Key", R"(software\microsoft\office\16.0\excel\options)");
		configXml->writeAttribute("Name", "defaultformat");
		configXml->writeAttribute("Value", "51");
		configXml->writeAttribute("Type", "REG_DWORD");
		configXml->writeAttribute("App", "excel16");
		configXml->writeAttribute("Id", "L_SaveExcelfilesas");
		configXml->writeEndElement();
	} else if(installerData.saveType == SaveType::OpenDoc) {
	}
}
