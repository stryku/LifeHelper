#pragma once

#include "program2internals/ProgramInfo.hpp"

#include "communication/Proxy.hpp"
#include "communication/AddressProviders.hpp"
#include "communication/ZmqFrontendBackendBinder.hpp"
#include "communication/ChannelFactory.hpp"
#include "subprograms/Process/ProcessFactory.hpp"
#include "subprograms/SubprogramInstance.hpp"

#include "tiny_process_library/process.hpp"

#include <QTabWidget>

#include <boost/variant.hpp>

#include <unordered_map>
#include <string>
#include <atomic>

namespace God
{
    namespace Subprograms
    {
        template <typename ProxyGodToSubprogram, typename ProxySubprogramToGod>
        class SubprogramInstancesManager
        {
        private:

            using Program2Instance = Instance<P2::Info::TypesPack, 
                                              Messages::Handlers::Program2, 
                                              Common::Communication::ChannelFactory>;

            using InstanceVariant = boost::variant<Program2Instance, int>;

            void createProgram2(QWidget *tab)
            {
                auto modelId = generateModelId();
                instances.emplace(genericCreate<P2::Info::TypesPack, Messages::Handlers::Program2, Common::Communication::ChannelFactory>(tab, modelId));
                processess.emplace(std::make_pair(modelId, Process::Factory::create(modelId)));
            }

            template <typename TypesPack, 
                      typename MessageHandler, 
                      typename Factory>
            auto genericCreate(QWidget *tab, ModelId modelId)
            {
                using InstanceType = Instance<TypesPack, MessageHandler, Factory>;

                InstanceType instance{ tab,
                                       proxyGodToSubprogram.subscriberAddress(),
                                       proxySubprogramToGod.publisherAddress(),
                                       getSubscribeString(modelId),
                                       createSignalHandler(modelId) };

                return std::make_pair(modelId, std::move(instance));
            }

        public:
            SubprogramInstancesManager(QTabWidget &tabWidget,
                                       ProxyGodToSubprogram &&proxyGodToSubprogram,
                                       ProxySubprogramToGod &&proxySubprogramToGod) :
                tabWidget{ tabWidget },
                proxyGodToSubprogram{ std::move(proxyGodToSubprogram) }, 
                proxySubprogramToGod{ std::move(proxySubprogramToGod) }
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
            std::unordered_map<ModelId, tpl::Process> processess;
            QTabWidget &tabWidget;

            ProxyGodToSubprogram proxyGodToSubprogram;
            ProxySubprogramToGod proxySubprogramToGod;
        };
    }
}