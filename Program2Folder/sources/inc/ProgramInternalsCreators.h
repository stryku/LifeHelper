#ifndef PROGRAMFACTORY_H
#define PROGRAMFACTORY_H

//#include "program2internals/ProgramInternals.h"
#include "ProgramInstance.hpp"
//#include "program2internals/view/QtView.h"
//#include "program2internals/model/Model.h"
//#include "program2internals/controller/Controller.h"
//#include "program2internals/model/SocketModelObserverSender.hpp"
//#include "program2internals/input/SocketInputPropagatorReceiver.h"

#include "program2internals/view/QtView.hpp"
//#include "program2internals/controller/Controller.h"
#include "program2internals/input/InputHandler.hpp"
#include "program2internals/input/InputPropagator.hpp"
#include "program2internals/input/SocketInputPropagatorSender.hpp"
#include "program2internals/model/SocketModelSender.hpp"
#include "program2internals/model/SocketModelReceiver.hpp"
//#include "program2internals/ProgramInternals.h"
#include "program2internals/model/Model.hpp"
#include "communication/OneWayChannel.hpp"
#include "Communication/ChannelFactory.hpp"

#include "program2internals/view/SocketView.hpp"

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
        using Instance = P2::Instance<View, InputPropagator, InputHandler, Model, ModelObserver>;
    }


    class Creator
    {
        /*using LocalQtInstance = P2::Instance<
            P2::Controller::Controller<P2::Model::Model>,
            P2::View::QtView<P2::Input::InputPropagator>,
            P2::Input::InputPropagator,
            P2::Model::Model,
            P2::ProgramInternals<P2::Controller::Controller<P2::Model::Model>>,
            QWidget>;

        using RemoteInstance = P2::Instance<
            P2::Controller::Controller<P2::Model::Model>,
            P2::Model::SocketModelObserverSender,
            P2::Input::SocketInputPropagatorReceiver,
            P2::Model::Model,
            P2::ProgramInternals<P2::Controller::Controller<P2::Model::Model>>,
            void
        >;*/

        /*using View = P2::View::QtView;
        using ModelObserver = P2::Model::ModelObserver<View>;
        using Model = P2::Model::Model<ModelObserver>;
        using InputHandler = P2::Input::InputHandler<Model>;
        using InputPropagator = P2::Input::InputPropagator<InputHandler>;
        using LocalQtInstance = P2::Instance<View, InputPropagator, InputHandler, Model, ModelObserver, QWidget>;*/

        
        /*using RemoteView = P2::View::SocketView<Common::Communication::PublisherChannel>;
        using RemoteModelObserver = P2::Model::ModelObserver<View>;
        using RemoteModel = P2::Model::Model<ModelObserver>;
        using RemoteInputHandler = P2::Input::InputHandler<Model>;
        using RemoteInputPropagator = P2::Input::InputPropagator<InputHandler>;
        using RemoteViewInstance = P2::Instance<RemoteView, RemoteInputPropagator, RemoteInputHandler, RemoteModel, RemoteModelObserver, QWidget>;*/

        //using ModelSender = P2::Model::Model
        ////////using InputHandler = P2::Input::InputHandler<ModelSender>;
        //using InputPropagator = Input::InputPropagator<InputHandler>;
        //using View = View::QtView<InputPropagator>;
        //using ModelObserver = P2::Model::ModelObserver<View>;
        //using ModelReceiver = P2::Model::SocketModelReceiver<ModelObserver>;

    public:
        static LocalQt::Instance createLocalQt(QWidget *qtViewWidgetParent);
        static Remote::Instance createRemote();
        //static RemoteInstance createRemote();
    };
    /*using RemoteInstance = P2::Instance<
        P2::Controller::Controller<P2::Model::Model>,
        P2::
    >;*/
}

#endif // PROGRAMFACTORY_H
