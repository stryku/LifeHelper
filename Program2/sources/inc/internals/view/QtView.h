#ifndef P2QTVIEW_H
#define P2QTVIEW_H

#include <internals/input/Input.h>
#include <internals/view/View.h>
#include <internals/view/detail/QtWidgetManager.h>

namespace P2
{
    namespace View
    {
        class QtView : public View
        {
        public:
            QtView( QWidget *widgetParent ) :
                widgetManager( widgetParent )
            {}

            void updateLabel( const QString &str )
            {
                widgetManager.setLabelSum( str );
            }

            void connectWithInput( Input::InputPropagator *input )
            {
                widgetManager.connectWithInput( input );
            }

            void updateSum( size_t newSum )
            {
                updateLabel( QString::number( newSum ) );
            }

        private:
            detail::QtWidgetManager widgetManager;
        };
    }
}

#endif // P2QTVIEW_H
