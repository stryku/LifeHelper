#ifndef P2QTVIEW_H
#define P2QTVIEW_H

#include <internals/input/P2Input.h>
#include <internals/view/P2View.h>
#include <internals/view/detail/P2QtWidgetManager.h>

class P2QtView : public P2View
{
public:
    P2QtView(QWidget *widgetParent) :
        widgetManager(widgetParent)
    {
    }

    void updateLabel(const QString &str)
    {
        widgetManager.setLabelSum(str);
    }

    void connectWithInput(P2InputPropagator *input)
    {
        widgetManager.connectWithInput(input);
    }

    void updateSum(size_t newSum)
    {
        updateLabel(QString::number(newSum));
    }

private:
    P2QtWidgetManager widgetManager;
};


#endif // P2QTVIEW_H
