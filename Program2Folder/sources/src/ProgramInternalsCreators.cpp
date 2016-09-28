#include "ProgramInternalsCreators.h"
#include "utils/log.hpp"

//#include <program2internals/model/SocketModelObserverReceiver.hpp>
#include "program2internals/model/SocketModelObserverSender.hpp"
#include "program2internals/input/SocketInputPropagatorSender.hpp"
//#include <program2internals/input/SocketInputObserverReceiver.h>


namespace ProgramInternalsCreators
{

    //Instance(ParentPlaceholder *parent) :
    //    //internals{ controller },
    //    view{ std::make_shared<View>(parent, "C:/moje/programowanie/LifeController/bin/programs/Program2/uiforms/Program2Form.ui") },
    //    inputPropagator{ std::make_shared<InputPropagator>() },
    //    modelObserver { std::make_shared<ModelObserver>() },
    //    model{ std::make_shared<Model>() },
    //    inputHandler { std::make_shared<InputHandler>(model) }
    //{
    //    view->connectWithInput(*inputPropagator);
    //    model->registerObserver(modelObserver);
    //    modelObserver->registerView(view);
    //    inputPropagator->setInputHandler(inputHandler);
    //    //inputHandler->setInputObserver(model);

    //    //internals.setController(controller);
    //    //internals.addInputPropagator(inputPropagator);
    //    //internals.addView(view);
    //}
    LocalQt::Instance Creator::createLocalQt(QWidget *qtViewWidgetParent)
    {
        LOG("creating local qt");

        /*using View = P2::View::QtView;
        using ModelObserver = P2::Model::ModelObserver<View>;
        using Model = P2::Model::Model<ModelObserver>;
        using InputHandler = P2::Input::InputHandler<Model>;
        using InputPropagator = P2::Input::InputPropagator<InputHandler>;
        using LocalQtInstance = P2::Instance<View, InputPropagator, InputHandler, Model, ModelObserver, QWidget>;*/

        LocalQt::Instance instance;

        instance.view = std::make_shared<LocalQt::View>(qtViewWidgetParent, "C:/moje/programowanie/LifeController/bin/programs/Program2/uiforms/Program2Form.ui");
        instance.inputPropagator = std::make_shared<LocalQt::InputPropagator>();
        instance.modelObserver = std::make_shared<LocalQt::ModelObserver>();
        instance.model = std::make_shared<LocalQt::Model>();
        instance.inputHandler = std::make_shared<LocalQt::InputHandler>(instance.model);

        instance.view->connectWithInput(*instance.inputPropagator);
        instance.model->registerObserver(instance.modelObserver);
        instance.modelObserver->registerView(instance.view);
        instance.inputPropagator->setInputHandler(instance.inputHandler);
            

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

        return instance;
    }

    Remote::Instance Creator::createRemote()
    {
        using ChannelFactory = Common::Communication::ChannelFactory;

        LOG("creating remote instance");

        Remote::Instance instance;

        instance.view = std::make_shared<Remote::View>(ChannelFactory::create<Remote::SocketViewSender>());
        instance.inputPropagator = std::make_shared<Remote::InputPropagator>();
        instance.modelObserver = std::make_shared<Remote::ModelObserver>();
        instance.model = std::make_shared<Remote::Model>();
        instance.inputHandler = std::make_shared<Remote::InputHandler>(instance.model);

        return instance;
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
