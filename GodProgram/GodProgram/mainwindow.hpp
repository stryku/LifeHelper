#pragma once

#include "subprograms/helpers.hpp"

#include <QMainWindow>

#include <functional>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setCreateNewInstanceCallback(std::function<void(God::Subprograms::Type, QWidget*)> callback)
    {
        createNewInstanceCallback = callback;
    }
    QTabWidget& getTabWidget();

private slots:
    void on_tabWidget_tabBarClicked(int index);

private:
    void createNewTab();

    Ui::MainWindow *ui;

    std::function<void(God::Subprograms::Type, QWidget*)> createNewInstanceCallback;
};
