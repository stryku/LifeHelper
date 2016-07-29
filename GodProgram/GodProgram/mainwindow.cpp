#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "TabCreators.hpp"

#include <iostream>

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
    auto plusTabIndex = ui->tabWidget->count() - 1;

    if(index == plusTabIndex)
        createNewTab();
}

void MainWindow::createNewTab()
{
    //QWidget *newTab = new QWidget(ui->tabWidget);
    auto tabsCount = ui->tabWidget->count();
    //ui->tabWidget->insertTab(tabsCount - 1, newTab, "text");

    mngr = God::Creators::Tab::createProgram2(ui->tabWidget);
    ui->tabWidget->insertTab(tabsCount - 1, mngr->getWidget(), "text");
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    createNewTab();
}
