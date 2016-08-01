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
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setCreateNewInstanceCallback(std::function<void(God::Subprograms::Type)> callback)
    {
        createNewInstanceCallback = callback;
    }
    QTabWidget& getTabWidget();

private slots:
    void on_tabWidget_tabBarClicked(int index);

private:
    void createNewTab();

    Ui::MainWindow *ui;

    std::function<void(God::Subprograms::Type)> createNewInstanceCallback;
};

#endif // MAINWINDOW_H
