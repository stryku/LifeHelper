#include "program2internals/view/detail/QtWidgetManager.hpp"
#include "utils/log.hpp"

using namespace P2::View::detail;

namespace P2
{
    namespace View
    {
        namespace detail
        {
            QtWidgetManager::QtWidgetManager(QWidget *parent, const QString &uiFilePath) :
                formWidget{ createWidget(parent, uiFilePath) }
            {}

            void QtWidgetManager::setLabelSum(const QString &newString)
            {
                LOG_FILE("QtWidgetManager::setLabelSum");

                ui_labelSum->setText(newString);
            }

            void QtWidgetManager::updateLabel(const QString &str)
            {
                LOG_FILE("QtWidgetManager::updateLabel");
                ui_labelSum->setText(str);
            }

            


            QWidget* QtWidgetManager::getWidget()
            {
                LOG_FILE("QtWidgetManager::addView");
                return formWidget;
            }

            QWidget* QtWidgetManager::loadUiFile(const QString &path, QWidget *parent) const
            {
                QUiLoader loader;
                QFile file{ path };

                file.open(QFile::ReadOnly);

                auto widget = loader.load(&file, parent);
                file.close();

                return widget;
            }

            QWidget* QtWidgetManager::createWidget(QWidget *parent, const QString &uiFilePath)
            {
                auto widget = loadUiFile(uiFilePath);

                widget->setParent(parent);

                ui_labelSum = widget->findChild<QLabel*>("labelSum");
                ui_pushButtonMinus = widget->findChild<QPushButton*>("pushButtonMinus");

                return widget;
            }
        }
    }
}