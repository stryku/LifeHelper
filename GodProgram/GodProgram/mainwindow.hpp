#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <memory>

#include <QMainWindow>
#include <program2internals/view/detail/QtWidgetManager.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_tabWidget_tabBarClicked(int index);
    void on_tabWidget_currentChanged(int index);

private:
    void createNewTab();

    Ui::MainWindow *ui;

    std::unique_ptr<P2::View::detail::QtWidgetManager> mngr;
};

#endif // MAINWINDOW_H
