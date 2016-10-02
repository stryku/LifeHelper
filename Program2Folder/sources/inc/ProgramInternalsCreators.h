#pragma once

#include "ProgramInstance.hpp"
#include "ProgramRemoteInstance.hpp"

#include "program2internals/view/QtView.hpp"
#include "program2internals/input/InputHandler.hpp"
#include "program2internals/input/InputPropagator.hpp"
#include "program2internals/model/SocketModelSender.hpp"
#include "program2internals/model/SocketModelReceiver.hpp"
#include "program2internals/model/Model.hpp"
#include "program2internals/view/SocketView.hpp"
#include "program2internals/communication/MessageHandler.hpp"
#include "program2internals/communication/MessageParser.hpp"
#include "communication/OneWayChannel.hpp"
#include "communication/ChannelFactory.hpp"

#include <QTabWidget>

namespace ProgramInternalsCreators
{
    namespace LocalQt
    {
        using View = P2::View::QtView;
        using ModelObserver = P2::Model::ModelObserver<View>;
        using Model = P2::Model::Model<ModelObserver>;
        using InputHandler = P2::Input::InputHandler<Model>;
        using InputPropagator = P2::Input::InputPropagator<InputHandler>;
        using Instance = P2::Instance<View, InputPropagator, InputHandler, Model, ModelObserver>;
    }

    namespace Remote
    {
        using SocketViewSender = Common::Communication::PublisherChannel;
        using View = P2::View::SocketView<SocketViewSender>;
        using ModelObserver = P2::Model::ModelObserver<View>;
        using Model = P2::Model::Model<ModelObserver>;
        using InputHandler = P2::Input::InputHandler<Model>;
        using InputPropagator = P2::Input::InputPropagator<InputHandler>;
        using BaseInstance = P2::Instance<View, InputPropagator, InputHandler, Model, ModelObserver>;
        using MessageHandler = P2::Communication::MessageHandler<P2::Communication::MessageParser>;
        using Instance = P2::ProgramRemoteInstance<BaseInstance, MessageHandler>;
    }

    class Creator
    {
    public:
        static LocalQt::Instance createLocalQt(QWidget *qtViewWidgetParent);
        static Remote::Instance createRemote(const std::string &subscribeAddress,
                                             const std::string &publishAddress,
                                             const std::string &modelId);
    };
    
}
