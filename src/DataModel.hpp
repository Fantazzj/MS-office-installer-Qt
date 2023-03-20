#ifndef DATAMODEL_HPP
#define DATAMODEL_HPP

#include <QString>
#include <QStringList>

enum SaveType {
	NotNow,
	OpenXml,
	OpenDoc
};

struct Model {
	QStringList exPrograms;
	QStringList productLangs;
	QStringList proofingLangs;
	QString version;
	QString product;
	QString release;
	QString setupDir;
	SaveType saveType;
	bool updates;
};

#endif//DATAMODEL_HPP
