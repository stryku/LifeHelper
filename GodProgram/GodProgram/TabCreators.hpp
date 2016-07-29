#pragma once

#include <QWidget>

namespace God
{
    namespace Creators
    {
        namespace Tab
        {
            enum class ProgramType
            {
                Program2
            };

            QWidget* create(ProgramType program)
            {
                switch (program)
                {
                case God::Creators::Tab::ProgramType::Program2:
                    break;
                default:
                    break;
                }
            }

            QWidget* createProgram2()
            {
                static constexpr auto uiPath = "programs/Program2/";
                QWidget *widget;

            }
        }
    }
}
