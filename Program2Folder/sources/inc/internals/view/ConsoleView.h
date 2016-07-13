#ifndef P2CONSOLEVIEW_H
#define P2CONSOLEVIEW_H

#include <internals/input/Input.h>
#include <internals/view/View.h>

namespace P2
{
    namespace View
    {
        class ConsoleView : public View
        {
        public:
            ConsoleView() {}

            void updateLabel(/*const QString &str*/ )
            {
                //        widgetManager.setLabelSum(str);
            }

            void connectWithInput( Input::InputPropagator *input )
            {
                //        widgetManager.connectWithInput(input);
            }

            void updateSum( size_t newSum )
            {
                updateLabel(/*QString::number(newSum)*/ );
            }
        };
    }
}
#endif // P2CONSOLEVIEW_H
