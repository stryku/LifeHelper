#ifndef P2QTWIDGETMANAGER_H
#define P2QTWIDGETMANAGER_H

#include <internals/input/P2InputHandler.h>
#include <internals/input/P2Input.h>

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QUiLoader>
#include <QFile>

#include <functional>

class P2QtWidgetManager
{
public:
    explicit P2QtWidgetManager(QWidget *parent);

    void setLabelSum(const QString &newString)
    {
        ui_labelSum->setText(newString);
    }

    QWidget* loadUiFile(QWidget *parent = nullptr)
    {
        QUiLoader loader;

        QFile file("form2.ui");
        file.open(QFile::ReadOnly);

        QWidget *formWidget = loader.load(&file, parent);
        file.close();

        return formWidget;
    }

    QWidget* createWidget(QWidget *parent)
    {
        auto widget = loadUiFile();

        widget->setParent(parent);

        ui_labelSum = widget->findChild<QLabel*>("labelSum");
        ui_pushButtonMinus = widget->findChild<QPushButton*>("pushButtonMinus");

        return widget;
    }

    void updateLabel(const QString &str)
    {
        ui_labelSum->setText(str);
    }

    void connectWithInput(P2InputPropagator *input)
    {
        formWidget->connect(ui_pushButtonMinus, &QPushButton::clicked, input->createDecrementSumCallback());
    }

    void setWidgetParent(QWidget *parent)
    {
        formWidget->setParent(parent);
    }

private:
    void ui_pushButtonMinusClicked()
    {
//        notifyDecrementSum();
    }

    std::function<void()> createPushButtonMinusClickedSlot()
    {
        auto slot = [this] { ui_pushButtonMinusClicked(); };
        return slot;
    }

    QPushButton *ui_pushButtonMinus;
    QLabel *ui_labelSum;
    QWidget *formWidget;
};

#endif // P2QTWIDGETMANAGER_H
