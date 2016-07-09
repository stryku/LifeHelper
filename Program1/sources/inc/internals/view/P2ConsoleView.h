#ifndef P2CONSOLEVIEW_H
#define P2CONSOLEVIEW_H

#include <internals/input/P2Input.h>
#include <internals/view/P2View.h>

class P2ConsoleView : public P2View
{
public:
    P2ConsoleView();

    void updateLabel(/*const QString &str*/)
    {
//        widgetManager.setLabelSum(str);
    }

    void connectWithInput(P2InputPropagator *input)
    {
//        widgetManager.connectWithInput(input);
    }

    void updateSum(size_t newSum)
    {
        updateLabel(/*QString::number(newSum)*/);
    }
};

#endif // P2CONSOLEVIEW_H
