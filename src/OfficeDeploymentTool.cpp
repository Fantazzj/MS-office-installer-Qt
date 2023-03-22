#include "OfficeDeploymentTool.hpp"

OfficeDeploymentTool::OfficeDeploymentTool(const Model& installerData) {
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
	/*QStringList args;
	args << "/configure" << configFile;
	setup.start(setupFile, args);
	setup.waitForFinished(-1);
	return 0;*/
	for(int j = 0; j < 10; j++) {
		qInfo() << "I'm working" << j;
		QThread::msleep(1000);
	}
	return 0;
}
