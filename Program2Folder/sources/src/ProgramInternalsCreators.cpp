#include "ProgramInternalsCreators.h"
#include "utils/log.hpp"

namespace ProgramInternalsCreators
{

    LocalQt::Instance Creator::createLocalQt(QWidget *qtViewWidgetParent)
    {
        LOG("creating local qt");
        
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

        return instance;
    }

    Remote::Instance Creator::createRemote(const std::string &subscribeAddress, 
                                           const std::string &publishAddress, 
                                           const std::string &modelId)
    {
        using ChannelFactory = Common::Communication::ChannelFactory;

        LOG("creating remote instance");

        Remote::BaseInstance baseInstance;

        baseInstance.view = std::make_shared<Remote::View>(ChannelFactory::create<Remote::SocketViewSender>());
        baseInstance.inputPropagator = std::make_shared<Remote::InputPropagator>();
        baseInstance.modelObserver = std::make_shared<Remote::ModelObserver>();
        baseInstance.model = std::make_shared<Remote::Model>();
        baseInstance.inputHandler = std::make_shared<Remote::InputHandler>(baseInstance.model);

        baseInstance.model->registerObserver(baseInstance.modelObserver);
        baseInstance.modelObserver->registerView(baseInstance.view);
        baseInstance.inputPropagator->setInputHandler(baseInstance.inputHandler);
        baseInstance.view->connect(publishAddress);

        auto messageHandler = std::make_shared<Remote::MessageHandler>();
        messageHandler->connectWithInput(*baseInstance.inputPropagator);

        Remote::Instance instance{ std::move(baseInstance), modelId, std::move(messageHandler) };

        return instance;
    }
}
