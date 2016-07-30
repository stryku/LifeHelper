#include <ProgramInternalsCreators.h>

#include <communication/CommunicationChannel.hpp>

#include <program2internals/model/SocketModelObserverReceiver.hpp>
#include <program2internals/model/SocketModelObserverSender.hpp>
#include <program2internals/input/SocketInputObserverSender.hpp>
#include <program2internals/input/SocketInputObserverReceiver.h>

#include <program2internals/view/QtView.h>

namespace ProgramInternalsCreators
{
    P2::ProgramInternals createLocalQt(QWidget *qtViewWidgetParent)
    {
        auto model = new P2::Model::Model();
        auto controller = new P2::Controller::Controller();
        auto inputPropagator = new P2::Input::InputPropagator();
        auto view = new P2::View::QtView( qtViewWidgetParent );

        view->connectWithInput( inputPropagator );
        model->registerObserver( controller );
        controller->registerView( view );
        controller->setInputObserver( model );

        auto internals = P2::ProgramInternals(controller);


        internals.setController( controller );
        internals.addInput( inputPropagator );
        internals.addView( view );

        return internals;
    }

    P2::ProgramInternals createRemoteModelQt(QWidget *qtViewWidgetParent)
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
    }

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
}
