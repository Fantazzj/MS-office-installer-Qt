#ifndef OFFICEDEPLOYMENTTOOL_H
#define OFFICEDEPLOYMENTTOOL_H

#include <QDebug>
#include <QMessageBox>
#include <QProcess>
#include <QThread>

#include "DataModel.hpp"

class OfficeDeploymentTool {
public:
	OfficeDeploymentTool(const Model& installerData);
	~OfficeDeploymentTool();
	int install();

private:
	QProcess setup;
	QString configFile;
	QString setupFile;
};

#endif//OFFICEDEPLOYMENTTOOL_H
