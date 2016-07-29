#ifndef P2QTVIEW_H
#define P2QTVIEW_H

#include <program2internals/input/Input.h>
#include <program2internals/view/View.h>
#include <program2internals/view/detail/QtWidgetManager.h>

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
