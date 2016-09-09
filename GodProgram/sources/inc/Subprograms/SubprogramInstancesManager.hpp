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

            void createProgram2(QWidget *tab)
            {
                instances.emplace(genericCreate<P2::Info::TypesPack, Messages::Handlers::Program2>(tab));
            }

            template <typename TypesPack, typename MessageHandler, typename InstanceType = Instance<TypesPack, MessageHandler>>
            auto genericCreate(QWidget *tab)
            {
                
                auto modelId = generateModelId();
                InstanceType instance{ tab,
                    proxy.getContext(),
                    proxy.getPushAddr(),
                    proxy.getSubAddr(),

                    getSubscribeString(modelId),
                    createSignalHandler(modelId)
                };

                return std::make_pair(modelId, std::move(instance));
            }

        public:
            SubprogramInstancesManager(QTabWidget &tabWidget, Proxy &proxy) :
                tabWidget{ tabWidget },
                proxy{ proxy }
            {}

            void create(Type subprogramType, QWidget *tab)
            {
                switch (subprogramType)
                {
                case God::Subprograms::Type::P2:
                    createProgram2(tab);
                    break;

                default:
                    //todo log
                    break;
                }
            }

            auto getCreateNewInstanceCallback()
            {
                return [this](Type subprogramType, QWidget *tab) { create(subprogramType, tab); };
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

            SignalsHandler createSignalHandler(ModelId id) const noexcept
            {
                auto heartbeatCallback = [this, id] { handleHeartbeat(id); };
                auto errorCallback = [this, id] (const std::string &errorMsg) { handleError(id, errorMsg); };
                auto cleanCloseCallback = [this, id] { handleCleanClose(id); };

                return{ SignalsHandlers{heartbeatCallback, errorCallback, cleanCloseCallback } };
            }

            void handleHeartbeat(ModelId id) const noexcept
            {}

            void handleError(ModelId id, const std::string &errorMsg) const noexcept
            {}

            void handleCleanClose(ModelId id) const noexcept
            {}

            std::unordered_map<ModelId, InstanceVariant> instances;
            QTabWidget &tabWidget;

            Proxy &proxy;
        };
    }
}