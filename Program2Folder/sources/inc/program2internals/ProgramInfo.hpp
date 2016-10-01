#pragma once

#include "view/QtView.hpp"
#include "input/InputHandler.hpp"
#include "input/InputPropagator.hpp"
#include "model/SocketModelSender.hpp"
#include "model/SocketModelReceiver.hpp"
#include "model/ModelObserver.hpp"
#include "communication/OneWayChannel.hpp"
#include "Communication/ChannelFactory.hpp"

namespace P2
{
    namespace Info
    {
        struct TypesPack
        {
            /*using View = View::QtView<Input::InputPropagator>;
            using SocketInputPropagatorSender = Input::SocketInputPropagatorSender<Common::Communication::PublisherChannel>;
            using Controller = Controller::Controller<SocketInputPropagatorSender, View>;
            using InputPropagator = Input::InputPropagator<Controller>;
            using ProgramInternals = ProgramInternals<Controller>;*/

            using ModelSender = Model::SocketModelSender<Common::Communication::PublisherChannel, 
                                                         Common::Communication::ChannelFactory>;
            using InputHandler = P2::Input::InputHandler<ModelSender>;
            using InputPropagator = Input::InputPropagator<InputHandler>;
            using View = View::QtView;
            using ModelObserver = P2::Model::ModelObserver<View>;
            using ModelReceiver = P2::Model::SocketModelReceiver<ModelObserver>;
        };

        static constexpr auto programName = "Program2";
        static constexpr auto uiFile = "Program2Form.ui";
    }
}