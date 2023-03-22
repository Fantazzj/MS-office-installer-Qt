#ifndef OFFICEDEPLOYMENTTOOL_H
#define OFFICEDEPLOYMENTTOOL_H

#include <QDebug>
#include <QProcess>

#include "DataModel.hpp"

class OfficeDeploymentTool {
public:
	OfficeDeploymentTool(Model installerData);
	~OfficeDeploymentTool();
	int install();

private:
	QProcess setup;
	QString configFile;
	QString setupFile;
};

#endif//OFFICEDEPLOYMENTTOOL_H
