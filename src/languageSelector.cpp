#include "languageSelector.hpp"
#include "ui_languageSelector.h"

languageSelector::languageSelector(QDialog* parent) :
	QDialog(parent), ui(new Ui::languageSelector) {

}

languageSelector::~languageSelector() {
	delete ui;
}
