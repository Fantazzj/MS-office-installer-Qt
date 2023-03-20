#ifndef OFFICEDEPLOYMENTTOOL_H
#define OFFICEDEPLOYMENTTOOL_H

#include <QProcess>
#include <QDebug>

#include "DataModel.hpp"

class OfficeDeploymentTool {
public:
	OfficeDeploymentTool(Model installerData);
	int install();
	//int download();

private:
	QProcess setup;
	Model installerData;
};

#endif//OFFICEDEPLOYMENTTOOL_H
