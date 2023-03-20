#include "OfficeDeploymentTool.hpp"

OfficeDeploymentTool::OfficeDeploymentTool(QString setupFile, QString configFile) {
	this->setupFile = setupFile;
	this->configFile = configFile;
	setupDir = setupFile;
	setupDir.remove("setup.exe");
	qDebug() << setupDir;
}

int OfficeDeploymentTool::install() {
	QStringList args;
	args << "/configure" << configFile;
	setup.start(setupFile, args);
	return 0;
}

int OfficeDeploymentTool::download() {
	QStringList args;
	args << "/download" << configFile;
	setup.setWorkingDirectory(setupDir);
	setup.start(setupFile, args);
	setup.waitForFinished(-1);
	return 0;
}
