#include <communication/CommunicationChannel.hpp>
#include <utils/log.hpp>
#include <utils/message_builders/XmlMessageBuilder.hpp>

using namespace Common::Communication;

CommunicationChannel::CommunicationChannel(zmq::context_t &context) :
    m_receiver(context),
    m_sender(context),
    m_pubProxy(context, zmq::socket_type::pub)
{}

CommunicationChannel::CommunicationChannel(CommunicationChannel &&other) noexcept :
    m_receiver(std::move(other.m_receiver)),
    m_sender(std::move(other.m_sender)),
    m_pubProxy(std::move(other.m_pubProxy))
{}

CommunicationChannel& CommunicationChannel::operator=(CommunicationChannel &&other) noexcept
{
    m_receiver = std::move(other.m_receiver);
    m_sender = std::move(other.m_sender);
    m_pubProxy = std::move(other.m_pubProxy);
    return *this;
}

auto CommunicationChannel::recv()
{
    zmq::message_t message;
    
    while (true)
    {
        try
        {
            m_receiver.recv(message);
            return message;
        }
        catch (zmq::error_t &err)
        {
            LOG("Exception cought at zmq::recv: " << err.what());
        }
    }
}

auto CommunicationChannel::send(zmq::message_t &message)
{
    try
    {
        return m_sender.send(message);
    }
    catch (zmq::error_t &err)
    {
        LOG("Exception cought at zmq::send: " << err.what());
        return false;
    }
}

auto CommunicationChannel::bind(const std::string &addr)
{
    return m_receiver.bind(addr);
}

auto CommunicationChannel::connect(const std::string &addr)
{
    return m_receiver.connect(addr);
}