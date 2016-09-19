#pragma once

#include "view/QtView.h"
#include "controller/Controller.h"
#include "input/Input.h"
#include "input/SocketInputPropagatorSender.hpp"
#include "ProgramInternals.h"
#include "communication/OneWayChannel.hpp"

namespace P2
{
    namespace Info
    {
        struct TypesPack
        {
            using InputPropagator = Input::InputPropagator;
            using View = View::QtView<InputPropagator>;
            using SocketInputPropagatorSender = Input::SocketInputPropagatorSender<Common::Communication::PublisherChannel>;
            using Controller = Controller::Controller<SocketInputPropagatorSender, View>;
            using ProgramInternals = ProgramInternals<Controller>;
        };

        static constexpr auto programName = "Program2";
        static constexpr auto uiFile = "Program2Form.ui";
    }
}