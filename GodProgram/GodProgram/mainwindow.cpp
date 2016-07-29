#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_tabWidget_tabBarClicked(int index)
{
    createNewTab();
}

void MainWindow::createNewTab()
{
    ui->tabWidget->addTab(nullptr, "text");
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    createNewTab();
}
