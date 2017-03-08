#include "mainwindow.h"
#include <QApplication>
#include <QObject>
#include <QDebug>

#include "ctrl/doc.h"

using rt::ctrl::Doc;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Doc d;
    MainWindow w;

    QObject::connect(&w, SIGNAL(toOpenFile(QString)), &d, SLOT(loadSceneFromFile(QString)));
    QObject::connect(&d, SIGNAL(information(QString)), &w, SLOT(showInfo(QString)));
    QObject::connect(&d, SIGNAL(warning(QString)), &w, SLOT(showWarning(QString)));
    QObject::connect(&d, SIGNAL(error(QString)), &w, SLOT(showError(QString)));

    w.show();

    return a.exec();
}
