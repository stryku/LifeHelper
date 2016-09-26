#include "ProgramInternalsCreators.h"
#include "utils/log.hpp"

//#include <program2internals/model/SocketModelObserverReceiver.hpp>
#include "program2internals/model/SocketModelObserverSender.hpp"
#include "program2internals/input/SocketInputPropagatorSender.hpp"
//#include <program2internals/input/SocketInputObserverReceiver.h>


namespace ProgramInternalsCreators
{
    Creator::LocalQtInstance Creator::createLocalQt(QWidget *qtViewWidgetParent)
    {
        LOG("creating local qt internals");

       /* using Model = P2::Model::Model;
        using Controller = P2::Controller::Controller<Model>;
        using InputPropagator = P2::Input::InputPropagator;
        using View = P2::View::QtView<InputPropagator>;
        using Internals = P2::ProgramInternals<Controller>;
        using Instance = Creator::LocalQtInstance;*/



        /*auto model = new P2::Model::Model();
        auto controller = new P2::Controller::Controller();
        auto inputPropagator = new P2::Input::InputPropagator();
        auto view = new P2::View::QtView( qtViewWidgetParent );

        view->connectWithInput( inputPropagator );
        model->registerObserver( controller );
        controller->registerView( view );
        controller->setInputObserver( model );*/

        //auto internals = P2::ProgramInternals(controller);


        //internals.setController( controller );
        //internals.addInputPropagator( inputPropagator );
        //internals.addView( view );

        return LocalQtInstance{ qtViewWidgetParent };
    }
   /* P2::ProgramInternals createRemoteModelQt(QWidget *qtViewWidgetParent)
    {
        zmq::context_t context{ 1 };
        Common::Communication::CommunicationChannel channel(context);

        auto modelChanges = new P2::Model::SocketModelChangesReceiver(channel.getReceiver());
        auto inputObserver = new P2::Input::SocketInputObserverSender(channel.getSender());

        auto controller = new P2::Controller::Controller();
        auto inputPropagator = new P2::Input::InputPropagator();
        auto view = new P2::View::QtView(qtViewWidgetParent);

        modelChanges->addModelObserver(controller);
        view->connectWithInput(inputPropagator);
        controller->registerView(view);
        controller->setInputObserver(inputObserver);

        auto internals = P2::ProgramInternals(controller);


        internals.setController(controller);
        internals.addInput(inputPropagator);
        internals.addView(view);

        return internals;
    }*/

   /* P2::ProgramInternals createRemoteViewRemoteInputLocalModel()
    {
        zmq::context_t context{ 1 };
        Common::Communication::CommunicationChannel channel(context);

        auto model = new P2::Model::Model();
        auto modelObserverSender = new P2::Model::SocketModelObserverSender(channel.getSender());
        auto inputChangesObserver = new P2::Input::SocketInputObserverReceiver(channel.getReceiver());

        model->registerObserver(modelObserverSender);
        inputChangesObserver->addInputObserver(model);

        auto internals = P2::ProgramInternals(controller);

        return internals;
    }
*/
/*
    Creator::RemoteInstance Creator::createRemote()
    {
        return RemoteInstance{nullptr};
    }*/
}
