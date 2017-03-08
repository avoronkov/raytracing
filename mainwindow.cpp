#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "ctrl/doc.h"
#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    doc{nullptr}
{
    ui->setupUi(this);
    connect(ui->actionOpen, SIGNAL(triggered(bool)), this, SLOT(openFile()));
    connect(ui->actionQuit, SIGNAL(triggered(bool)), this, SLOT(close()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::setDoc(rt::ctrl::Doc * d)
{
    doc = d;
    ui->display->setDocument(doc);
    ui->display->update();
}

void MainWindow::openFile()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open file"), "..", tr("Scene files (*.txt)"));
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

void MainWindow::updateView() {
    ui->display->update();
}
