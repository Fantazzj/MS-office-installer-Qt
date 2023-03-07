#ifndef LANGUAGESELECTOR_HPP
#define LANGUAGESELECTOR_HPP

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
	class languageSelector;
}
QT_END_NAMESPACE

class languageSelector : public QDialog {
	Q_OBJECT

public:
	languageSelector(QDialog* parent = nullptr);
	~languageSelector();

private slots:

private:
	Ui::languageSelector* ui;
};



#endif//LANGUAGESELECTOR_HPP
