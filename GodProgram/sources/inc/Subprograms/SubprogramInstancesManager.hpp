#pragma once

#include <program2internals/ProgramInfo.hpp>

#include <Subprograms/SubprogramInstanceFactory.hpp>

#include <boost/variant.hpp>

#include <unordered_map>
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
            using Program2Instance = Instance<P2::Info::TypesPack, Messages::Handlers::Program2>;

            using InstanceVariant = boost::variant<Program2Instance, int>;

            //struct InstanceWithHandler
            //{
            //    InstanceWithHandler(SignalsHandler &&handler, InstanceVariant &&instance) :
            //        instance{ std::move(instance) },
            //        handler{ std::move(handler) }
            //    {}
            //    InstanceWithHandler(const InstanceWithHandler&) = delete;
            //    InstanceWithHandler& operator=(const InstanceWithHandler&) = delete;

            //    InstanceWithHandler(InstanceWithHandler &&other) :
            //        instance{ std::move(other.instance) },
            //        handler{ std::move(other.handler) },
            //        modelId{ std::move(other.modelId) }
            //    {}

            //    InstanceWithHandler& operator=(InstanceWithHandler &&other)
            //    {
            //        instance = std::move(other.instance);
            //        handler = std::move(other.handler);
            //        modelId = std::move(other.modelId);

            //        return *this;
            //    }

            //    //InstanceVariant instance;
            //    SignalsHandler handler;
            //    ModelId modelId;
            //};

            template <typename TypesPack, typename MessageHandler, typename InstanceType = Instance<TypesPack, MessageHandler>>
            class Builder
            {
            public:

            private:
                InstanceType instance;
            };     


            void createProgram2()
            {
                Instance<P2::Info::TypesPack, Messages::Handlers::Program2> instance{ genericCreate<P2::Info::TypesPack, Messages::Handlers::Program2>() };
                //auto id = instance.modelId;

                //instances[id] = std::move(instance);
            }

            template <typename TypesPack, typename MessageHandler, typename InstanceType = Instance<TypesPack, MessageHandler>>
            InstanceType genericCreate()
            {
                
                auto modelId = generateModelId();
                InstanceType instance{ std::ref(tabWidget),
                    proxy.getContext(),
                    proxy.getPushAddr(),
                    proxy.getSubAddr(),

                    getSubscribeString(modelId),
                    createSignalHandler()
                };

                return std::move(instance);
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
                    createProgram2();
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

            std::unordered_map<ModelId, InstanceVariant> instances;
            QTabWidget &tabWidget;

            Proxy &proxy;
        };
    }
}