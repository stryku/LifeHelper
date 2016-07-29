#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(God::Tabs::TabsManager &tabsMngr, QWidget *parent) :
    QMainWindow(parent),
    ui{new Ui::MainWindow},
    tabsMngr{ tabsMngr }
{
    ui->setupUi(this);
    tabsMngr.setTabWidget(ui->tabWidget);
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
    tabsMngr.create(God::Subprograms::Type::P2, 0);
}
