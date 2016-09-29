#pragma once

#include "ProgramInstance.hpp"
#include "communication/MessagesSubscriber.hpp"
#include "communication/ChannelFactory.hpp"

namespace P2
{
    template <typename BaseInstance, typename MessageHandler>
    class ProgramRemoteInstance
    {
    public:
        ProgramRemoteInstance(BaseInstance &&baseInstance,
                              const std::string &subscribeString)
            : baseInstance{ std::move(baseInstance) }
            , messageHandler{ std::make_shared<MessageHandler>() }
            , messageSubscriber{subscribeString, messageHandler }
        {}

        ProgramRemoteInstance(ProgramRemoteInstance&&) = default;
        ProgramRemoteInstance& operator=(ProgramRemoteInstance&&) = default;

        ProgramRemoteInstance() = delete;
        ProgramRemoteInstance(const ProgramRemoteInstance&) = delete;
        ProgramRemoteInstance& operator=(const ProgramRemoteInstance&) = delete;

        void startListening(const std::string &connectString)
        {
            LOG_FILE("ProgramRemoteInstance::startListening on " << connectString);

            messageSubscriber.connect(connectString);
            messageSubscriber.startRecv();
        }

    private:
        using ChannelFactory = Common::Communication::ChannelFactory;
        using Subscriber = Common::Communication::Subscriber<MessageHandler, ChannelFactory>;

        BaseInstance baseInstance;
        std::shared_ptr<MessageHandler> messageHandler;
        Subscriber messageSubscriber;
    };
}
