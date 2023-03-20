#ifndef OFFICEDEPLOYMENTTOOL_H
#define OFFICEDEPLOYMENTTOOL_H

#include <QProcess>
#include <QDebug>

class OfficeDeploymentTool {
public:
	OfficeDeploymentTool(QString setupFile, QString configFile);
	int install();
	int download();

private:
	QString setupFile;
	QString configFile;
	QString setupDir;
	QProcess setup;
};

#endif//OFFICEDEPLOYMENTTOOL_H
