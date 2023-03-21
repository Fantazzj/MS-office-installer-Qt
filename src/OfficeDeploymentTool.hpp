#ifndef OFFICEDEPLOYMENTTOOL_H
#define OFFICEDEPLOYMENTTOOL_H

#include <QProcess>
#include <QDebug>

#include "DataModel.hpp"

class OfficeDeploymentTool {
public:
	OfficeDeploymentTool(Model installerData);
	~OfficeDeploymentTool();
	int install();
	//int download();

private:
	QProcess setup;
	QString configFile;
	QString setupFile;
};

#endif//OFFICEDEPLOYMENTTOOL_H
