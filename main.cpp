#include <QApplication>
#include <QLibraryInfo>
#include <QLocale>
#include <QTranslator>

#include "src/installer.hpp"

int main(int argc, char* argv[]) {
	QApplication a(argc, argv);

	qDebug() << "Loading languages";
	const QStringList uiLanguages = QLocale::system().uiLanguages();

	QTranslator translator;
	for(const QString& locale: uiLanguages) {
		const QString baseName = "MS-office-installer_" + QLocale(locale).name();
		if(translator.load(":/i18n/" + baseName)) {
			a.installTranslator(&translator);
			break;
		}
	}

	QTranslator basic;
	for(const QString& locale: uiLanguages) {
		const QString baseName = "/qt_" + QLocale(locale).name();
		if(basic.load(QLibraryInfo::path(QLibraryInfo::TranslationsPath) + baseName)) {
			a.installTranslator(&basic);
			break;
		}
	}

	qDebug() << SEPARATOR;

	Installer w;
	w.show();
	return a.exec();
}
