#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

#include "ctrl/doc.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setDoc(rt::ctrl::Doc *);

public slots:
    void openFile();

    void showInfo(QString);
    void showWarning(QString);
    void showError(QString);

    void updateView();

signals:
    void toOpenFile(QString);

private:
    Ui::MainWindow *ui;

    rt::ctrl::Doc * doc;
};

#endif // MAINWINDOW_H
