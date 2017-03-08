#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionOpen, SIGNAL(triggered(bool)), this, SLOT(openFile()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openFile()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open file"), ".", tr("Scene files (*.txt)"));
    qDebug() << "opened file " << filename;
    if (filename.isEmpty()) return;
    emit toOpenFile(filename);
}

void MainWindow::showInfo(QString info)
{
    QMessageBox::information(this, "Information", info);
}

void MainWindow::showWarning(QString warning)
{
    QMessageBox::warning(this, "Warning", warning);
}

void MainWindow::showError(QString error)
{
    QMessageBox::critical(this, "Warning", error);
}
