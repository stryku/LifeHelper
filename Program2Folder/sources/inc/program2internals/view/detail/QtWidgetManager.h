#ifndef P2QTWIDGETMANAGER_H
#define P2QTWIDGETMANAGER_H

#include <program2internals/input/InputHandler.h>
#include <program2internals/input/Input.h>

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QUiLoader>
#include <QFile>

#include <functional>

namespace P2
{
    namespace View
    {
        namespace detail
        {
            class QtWidgetManager
            {
            public:
                explicit QtWidgetManager( QWidget *parent );

                void setLabelSum( const QString &newString );
                void updateLabel( const QString &str );
                void connectWithInput( Input::InputPropagator *input );

            private:
                QWidget* loadUiFile( const QString &path, QWidget *parent = nullptr ) const;
                QWidget* createWidget( QWidget *parent );

                QPushButton *ui_pushButtonMinus;
                QLabel *ui_labelSum;
                QWidget *formWidget;
            };
        }
    }
}

#endif // P2QTWIDGETMANAGER_H
