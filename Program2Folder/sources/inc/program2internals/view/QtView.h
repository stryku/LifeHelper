#ifndef P2QTVIEW_H
#define P2QTVIEW_H

#include <program2internals/input/Input.h>
#include <program2internals/view/View.h>
#include <program2internals/view/detail/QtWidgetManager.h>

namespace P2
{
    namespace View
    {
        template <typename InputPropagator>
        class QtView : public View
        {
        public:
            QtView( QWidget *widgetParent, const QString &uiFilePath ="C:/moje/programowanie/LifeController/bin/programs/Program2/uiforms/Program2Form.ui" ) :
                widgetManager( widgetParent, uiFilePath )
            {}

            void updateLabel( const QString &str )
            {
                LOG_FILE("InputPropagator::updateLabel(" << str.toStdString() << ")");

                widgetManager.setLabelSum( str );
            }

            void connectWithInput(InputPropagator *input )
            {
                LOG_FILE("InputPropagator::connectWithInput");
                widgetManager.connectWithInput( input );
            }

            void updateSum( size_t newSum )
            {
                LOG_FILE("InputPropagator::updateSum( " << newSum << " )");
                updateLabel( QString::number( newSum ) );
            }

        private:
            detail::QtWidgetManager widgetManager;
        };
    }
}

#endif // P2QTVIEW_H
