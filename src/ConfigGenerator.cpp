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

	QFile jsonFile = QFile("../res/contents.json");
	jsonFile.open(QIODevice::ReadOnly | QIODevice::Text);
	QString dummy = jsonFile.readAll();
	QJsonDocument jsonDoc = QJsonDocument::fromJson(dummy.toUtf8());
	jsonFile.close();
	_jsonObj = jsonDoc.object();

	_comboBoxPopulator(_ui->comboBoxVersion, "versions");
	_comboBoxPopulator(_ui->comboBoxProduct, "product");
	_comboBoxPopulator(_ui->comboBoxRelease, "releaseChannel");
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

	version = _ui->comboBoxVersion->currentData().toString();
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
	configXml->writeEndElement();//Language
}

void ConfigGenerator::_writeProofingLangsElements() {
	configXml->writeStartElement("Language");
	configXml->writeEndElement();//Language
}

void ConfigGenerator::_writeExcludeAppElements() {
	for(auto& A: apps)
		if(!A->isChecked()) {
			configXml->writeStartElement("ExcludeApp");
			configXml->writeAttribute("ID", A->objectName().remove("checkBox"));
			configXml->writeEndElement();//ExcludeApp
		}
}

void ConfigGenerator::_writeUpdatesElement() {
	configXml->writeStartElement("Updates");
	if(_ui->checkBoxUpdates->isChecked())
		configXml->writeAttribute("Enabled", "TRUE");
	else
		configXml->writeAttribute("Enabled", "FALSE");
}

void ConfigGenerator::_comboBoxPopulator(QComboBox* comboBox, QString key) {
	QJsonArray versions = _jsonObj.value(key).toArray();
	qDebug() << versions;
	for(QJsonValueRef A: versions) {
		qDebug() << A.toArray().at(0) << A.toArray().at(1);
		comboBox->addItem(A.toArray().at(0).toString(), A.toArray().at(1).toString());
	}
	qDebug() << SEPARATOR;
}
