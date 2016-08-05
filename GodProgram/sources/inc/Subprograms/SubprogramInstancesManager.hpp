#pragma once

#include <program2internals/ProgramInfo.hpp>

#include <Subprograms/SubprogramInstanceFactory.hpp>

#include <boost/any.hpp>

#include <unordered_set>
#include <string>
#include <atomic>

namespace God
{
    namespace Subprograms
    {


        struct Proxy
        {
            std::string getPushAddr()
            {
                return "tcp://127.0.0.1:5252";
            }

            std::string getSubAddr()
            {
                return "12";
            }

            zmq::context_t& getContext()
            {
                static zmq::context_t ctx{ 1 };
                return ctx;
            }
        };

        class SubprogramInstancesManager
        {
        private:

            template <typename InstanceType>
            struct InstanceWithHandler
            {
                InstanceWithHandler(SignalsHandler &&handler, InstanceType &&instance) :
                    instance{ std::move(instance) },
                    handler{ std::move(handler) }
                {}
                InstanceWithHandler(const InstanceWithHandler&) = delete;
                InstanceWithHandler& operator=(const InstanceWithHandler&) = delete;

                InstanceWithHandler(InstanceWithHandler &&other) :
                    instance{ std::move(other.instance) },
                    handler{ std::move(other.handler) },
                    modelId{ std::move(other.modelId) }
                {}

                InstanceWithHandler& operator=(InstanceWithHandler &&other)
                {
                    insatnce = std::move(other.instance);
                    handler = std::move(other.handler);
                    modelId = std::move(other.modelId);

                    return *this;
                }

                InstanceType instance;
                SignalsHandler handler;
                ModelId modelId;

                //bool operator==(const InstanceWithHandler &rhs) const
                //{
                //    return modelId == rhs.modelId;
                //}
                /*
                struct hash
                {
                    size_t operator()(const InstanceWithHandler &instance) const noexcept
                    {
                       return std::hash<ModelId>()(instance.modelId);
                    }
                };*/
            };


            auto createProgram2()
            {
                return std::move(genericCreate<P2::Info::TypesPack, Messages::Handlers::Program2>());
            }

            template <typename TypesPack, typename MessageHandler, typename InstanceType = Instance<TypesPack, MessageHandler>>
            InstanceWithHandler<InstanceType> genericCreate()
            {
                InstanceWithHandler<InstanceType> instanceWithHandler{ createSignalHandler(), 
                    InstanceFactory::create<TypesPack, MessageHandler>(tabWidget,
                                                                       proxy.getContext(),
                                                                       proxy.getPushAddr(),
                                                                       proxy.getSubAddr(),
                                                                       getSubscribeString(instanceWithHandler.modelId),
                                                                       &instanceWithHandler.handler) };

                instanceWithHandler.modelId = generateModelId();
                //auto&& ptr = 
                //instanceWithHandler.instance = { std::move(ptr) };

                return std::move(instanceWithHandler);
            }

            template <typename Element>
            void store(Element &&elem)
            {
                static std::vector<Element> instances;
                instances.push_back(std::move(elem));
            }

        public:
            SubprogramInstancesManager(QTabWidget &tabWidget, Proxy &proxy) :
                tabWidget{ tabWidget },
                proxy{ proxy }
            {}

            void create(Type subprogramType)
            {
                switch (subprogramType)
                {
                case God::Subprograms::Type::P2:
                    store(createProgram2());
                    break;

                default:
                    //todo log
                    break;
                }
            }

            auto getCreateNewInstanceCallback()
            {
                return [this](Type subprogramType) { create(subprogramType); };
            }


        private:

            ModelId generateModelId() const noexcept
            {
                static std::atomic<ModelId> id;
                return ++id;
            }
            static std::string getSubscribeString(ModelId id)
            {
                return std::to_string(id);
            }

            SignalsHandler createSignalHandler() const noexcept
            {
                auto heartbeatCallback = [this] { handleHeartbeat(); };
                auto errorCallback = [this] (const std::string &errorMsg) { handleError(errorMsg); };
                auto cleanCloseCallback = [this] { handleCleanClose(); };

                return{ SignalsHandlers{heartbeatCallback, errorCallback, cleanCloseCallback } };
            }

            void handleHeartbeat() const noexcept
            {}

            void handleError(const std::string &errorMsg) const noexcept
            {}

            void handleCleanClose() const noexcept
            {}

            //std::unordered_set<InstanceWithHandler, InstanceWithHandler::hash> instances;
            QTabWidget &tabWidget;

            Proxy &proxy;
        };
    }
}