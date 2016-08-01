#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui{new Ui::MainWindow}
    //tabsMngr{ tabsMngr }
{
    ui->setupUi(this);
    //tabsMngr.setTabWidget(ui->tabWidget);
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
    createNewInstanceCallback(God::Subprograms::Type::P2);
}


QTabWidget& MainWindow::getTabWidget()
{
    return *ui->tabWidget;
}
