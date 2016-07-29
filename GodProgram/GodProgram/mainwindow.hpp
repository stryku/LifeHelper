#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <Tabs/TabsManager.hpp>

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(God::Tabs::TabsManager &tabsMngr, QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_tabWidget_tabBarClicked(int index);

private:
    void createNewTab();

    Ui::MainWindow *ui;

    God::Tabs::TabsManager &tabsMngr;
};

#endif // MAINWINDOW_H
