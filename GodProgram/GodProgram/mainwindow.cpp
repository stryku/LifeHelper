#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui{new Ui::MainWindow}
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
    auto newTab = new QWidget(ui->tabWidget);
    auto plusTabIndex = ui->tabWidget->count() - 1;
    ui->tabWidget->insertTab(plusTabIndex, newTab, tr("P2"));

    createNewInstanceCallback(God::Subprograms::Type::P2, newTab);
}


QTabWidget& MainWindow::getTabWidget()
{
    return *ui->tabWidget;
}
