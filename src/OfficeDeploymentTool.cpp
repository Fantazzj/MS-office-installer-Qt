#include "OfficeDeploymentTool.hpp"

OfficeDeploymentTool::OfficeDeploymentTool(Model installerData) {
	/*this->setupFile = setupFile;
	this->configFile = configFile;
	setupDir = setupFile;
	setupDir.remove("setup.exe");
	qDebug() << setupDir;*/
	qDebug() << "OfficeDeploymentTool created";
	setupFile = installerData.setupDir + "/setup.exe";
	configFile = installerData.setupDir + "/config.xml";
	qDebug() << setupFile;
	qDebug() << configFile;
}

OfficeDeploymentTool::~OfficeDeploymentTool() {
	qDebug() << "OfficeDeploymentTool destroyed";
	qDebug() << SEPARATOR;
}

int OfficeDeploymentTool::install() {
	QStringList args;
	args << "/configure" << configFile;
	setup.start(setupFile, args);
	return 0;
}

/*int OfficeDeploymentTool::download() {
	QStringList args;
	args << "/download" << configFile;
	setup.setWorkingDirectory(setupDir);
	setup.start(setupFile, args);
	setup.waitForFinished(-1);
	return 0;
}*/
