#include <ecal/ecal.h>
#include <ecal/msg/protobuf/server.h>

#include <iostream>
#include <chrono>
#include <thread>
#include <math.h>
#include <cfloat>
#include <cmath>

#include "math_service.pb.h"

/**
 * @brief implement mathservice
 *
 */
class MathServiceImpl : public math_service_pb::MathService
{
public:
    /**
     * @brief add
     *
     */
    virtual void Add(
        ::google::protobuf::RpcController * /* controller_ */,
        const ::math_service_pb::SFloatTuple *request_,
        ::math_service_pb::SFloat *response_,
        ::google::protobuf::Closure * /* done_ */)
    {
        // print request and
        std::cout << "Received request MathService / Add      : " << request_->inp1() << " and " << request_->inp2() << std::endl
                  << std::endl;
        // create response
        response_->set_out(request_->inp1() + request_->inp2());
    }

    /**
     * @brief Multiply
     *
     */
    virtual void Multiply(
        ::google::protobuf::RpcController * /* controller_ */,
        const ::math_service_pb::SFloatTuple *request_,
        ::math_service_pb::SFloat *response_,
        ::google::protobuf::Closure * /* done_ */)
    {
        // print request and
        std::cout << "Received request MathService / Multiply : " << request_->inp1() << " and " << request_->inp2() << std::endl
                  << std::endl;
        // create response
        response_->set_out(request_->inp1() * request_->inp2());
    }

    /**
     * @brief divide
     *
     */
    virtual void Divide(
        ::google::protobuf::RpcController * /* controller_ */,
        const ::math_service_pb::SFloatTuple *request_,
        ::math_service_pb::SFloat *response_,
        ::google::protobuf::Closure * /* done_ */)
    {
        // print request and
        std::cout << "Received request MathService / Divide   : " << request_->inp1() << " and " << request_->inp2() << std::endl
                  << std::endl;
        // create response
        if (std::fabs(request_->inp2()) > DBL_EPSILON)
            response_->set_out(request_->inp1() / request_->inp2());
        else
            response_->set_out(0.0);
    }
};

/**
 * @brief server state callback
 *
 * @param data_
 */
void OnServerEvent(const eCAL::SServerEventCallbackData *data_)
{
    // check data
    assert(data_);

    switch (data_->type)
    {
    case eCAL_Server_Event::server_event_connected:
        std::cout << "-----------------------------------" << std::endl;
        std::cout << "Server connected                   " << std::endl;
        std::cout << "-----------------------------------" << std::endl;
        break;
    case eCAL_Server_Event::server_event_disconnected:
        std::cout << "-----------------------------------" << std::endl;
        std::cout << "Server disconnected                " << std::endl;
        std::cout << "-----------------------------------" << std::endl;
        break;
    default:
        std::cout << "Unknown server event." << std::endl;
        break;
    }
}

// main entry
int main(int argc, char **argv)
{
    // initialize eCAL API
    eCAL::Initialize(argc, argv, "math server");

    // create Math service server
    std::shared_ptr<math_service_pb::MathService> math_service = std::make_shared<MathServiceImpl>();
    eCAL::protobuf::CServiceServer<math_service_pb::MathService> math_server(math_service);

    // register event callbacks
    math_server.AddEventCallback(eCAL_Server_Event::server_event_connected, std::bind(OnServerEvent, std::placeholders::_2));
    math_server.AddEventCallback(eCAL_Server_Event::server_event_disconnected, std::bind(OnServerEvent, std::placeholders::_2));

    while (eCAL::Ok())
    {
        // sleep 100 ms
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    // finalize eCAL API
    eCAL::Finalize();

    return (0);
}