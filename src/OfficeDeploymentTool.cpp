#include "OfficeDeploymentTool.hpp"

OfficeDeploymentTool::OfficeDeploymentTool(Model installerData) {
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
