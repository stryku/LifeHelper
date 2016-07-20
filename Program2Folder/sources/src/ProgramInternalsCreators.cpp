#include <ProgramInternalsCreators.h>

#include <communication/CommunicationChannel.hpp>

#include <internals/model/SocketModelObserverReceiver.hpp>
#include <internals/model/SocketModelObserverSender.hpp>
#include <internals/input/SocketInputObserverSender.hpp>
#include <internals/input/SocketInputObserverReceiver.h>

#include <internals/view/QtView.h>

namespace ProgramInternalsCreators
{
    ProgramInternals createLocalQt( QWidget *qtViewWidgetParent )
    {
        auto model = new P2::Model::Model();
        auto controller = new P2::Controller::Controller();
        auto inputPropagator = new P2::Input::InputPropagator();
        auto view = new P2::View::QtView( qtViewWidgetParent );

        view->connectWithInput( inputPropagator );
        model->registerObserver( controller );
        controller->registerView( view );
        controller->setInputObserver( model );

        auto internals = ProgramInternals();


        internals.setController( controller );
        internals.addInput( inputPropagator );
        internals.addView( view );

        return internals;
    }

    ProgramInternals createRemoteModelQt(QWidget *qtViewWidgetParent)
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

        auto internals = ProgramInternals();


        internals.setController(controller);
        internals.addInput(inputPropagator);
        internals.addView(view);

        return internals;
    }

    ProgramInternals createRemoteViewRemoteInputLocalModel()
    {
        zmq::context_t context{ 1 };
        Common::Communication::CommunicationChannel channel(context);

        auto model = new P2::Model::Model();
        auto modelObserverSender = new P2::Model::SocketModelObserverSender(channel.getSender());
        auto inputChangesObserver = new P2::Input::SocketInputObserverReceiver(channel.getReceiver());

        model->registerObserver(modelObserverSender);
        inputChangesObserver->addInputObserver(model);

        auto internals = ProgramInternals();

        return internals;
    }

}
