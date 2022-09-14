#ifndef INSTALLER_H
#define INSTALLER_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
    class Installer;
}
QT_END_NAMESPACE

class Installer : public QMainWindow {
    Q_OBJECT

public:
    Installer(QWidget* parent = nullptr);
    ~Installer();

private:
    Ui::Installer* ui;
};
#endif// INSTALLER_H
