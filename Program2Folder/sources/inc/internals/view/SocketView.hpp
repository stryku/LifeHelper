#pragma once

#include "View.h"

#include <communication/CommunicationChannel.hpp>

namespace P2
{
    namespace View
    {
        class SocketView : public View
        {
        private:
            using Sender = Common::Communication::ChannelType::Sender;

        public:
            SocketView(Sender &sender)

            virtual void updateSum(size_t newSum) override
            {

            }


        };
    }
}