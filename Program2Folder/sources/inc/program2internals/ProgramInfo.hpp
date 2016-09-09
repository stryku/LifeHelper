#pragma once

#include "view/QtView.h"
#include "controller/Controller.h"
#include "input/Input.h"
#include "input/SocketInputObserverSender.hpp"
#include "ProgramInternals.h"

namespace P2
{
    namespace Info
    {
        struct TypesPack
        {
            using InputPropagator = Input::InputPropagator;
            using View = View::QtView<InputPropagator>;
            using SocketInputObserverSender = Input::SocketInputObserverSender;
            using Controller = Controller::Controller<SocketInputObserverSender>;
            using ProgramInternals = ProgramInternals<Controller>;
        };

        static constexpr auto programName = "Program2";
        static constexpr auto uiFile = "Program2Form.ui";
    }
}