#include "mainwindow.h"
#include <QApplication>
#include <QObject>
#include <QDebug>
#include <iostream>

#include "ctrl/doc.h"

using rt::ctrl::Doc;

void msgHandler(QtMsgType type, const QMessageLogContext &, const QString & msg)
{
    char sym;
    switch(type) {
    case QtDebugMsg: sym = 'D'; break;
    case QtInfoMsg: sym = 'I'; break;
    case QtWarningMsg: sym = 'W'; break;
    case QtCriticalMsg: sym = 'C'; break;
    case QtFatalMsg: sym = 'F'; break;
    default: sym = '?';
    }

    QString output = QString("[%1] %2").arg( sym ).arg( msg );
    std::cerr << output.toStdString() << std::endl;
    if( type == QtFatalMsg ) abort();
}


int main(int argc, char *argv[])
{
    qInstallMessageHandler( msgHandler );
    QApplication a(argc, argv);

    Doc d;
    MainWindow w;
    w.setDoc(&d);

    QObject::connect(&w, SIGNAL(toOpenFile(QString)), &d, SLOT(loadSceneFromFile(QString)));
    QObject::connect(&d, SIGNAL(information(QString)), &w, SLOT(showInfo(QString)));
    QObject::connect(&d, SIGNAL(warning(QString)), &w, SLOT(showWarning(QString)));
    QObject::connect(&d, SIGNAL(error(QString)), &w, SLOT(showError(QString)));
    QObject::connect(&d, SIGNAL(changed()), &w, SLOT(updateView()));

    w.show();

    return a.exec();
}
