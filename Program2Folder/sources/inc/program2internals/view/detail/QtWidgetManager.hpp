#pragma once

#include "utils/log.hpp"


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
                explicit QtWidgetManager( QWidget *parent, const QString &uiFilePath = "C:/moje/programowanie/LifeController/bin/programs/Program2/uiforms/Program2Form.ui" );

                void setLabelSum( const QString &newString );
                void updateLabel( const QString &str ); 

                template <typename InputPropagator>
                void QtWidgetManager::connectWithInput(InputPropagator &inputPropagator)
                {
                    LOG_FILE("QtWidgetManager::connectWithInput");
                    formWidget->connect(ui_pushButtonMinus,
                                        &QPushButton::clicked,
                                        inputPropagator.createDecrementSumCallback());
                }

                QWidget* getWidget();

            private:
                QWidget* loadUiFile( const QString &path, QWidget *parent = nullptr ) const;
                QWidget* createWidget( QWidget *parent, const QString &uiFilePath );

                QPushButton *ui_pushButtonMinus;
                QLabel *ui_labelSum;
                QWidget *formWidget;
            };
        }
    }
}
