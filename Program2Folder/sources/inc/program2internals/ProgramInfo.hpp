#pragma once

#include "view/View.h"
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
            using ProgramInternals = ProgramInternals;
            using View = View::View;
            using Controller = Controller::Controller;
            using InputPropagator = Input::InputPropagator;
            using SocketInputPropagator = Input::SocketInputObserverSender;
        };

        static constexpr auto programName = "Program2";
        static constexpr auto uiFile = "Program2Form.ui";
    }
}