#include <ecal/ecal.h>
#include <ecal/msg/protobuf/server.h>

#include <iostream>
#include <chrono>
#include <thread>

#include "ping_service.pb.h"

/**
 * @brief ping_service
 * 
 */
class PingServiceImpl : public PingService
{
public:
    void Ping(
        ::google::protobuf::RpcController * /* controller_ */, 
        const ::PingRequest *request_, 
        ::PingResponse *response_, 
        ::google::protobuf::Closure * /* done_ */)
    {
        // print request 
        std::cout << "Received request PingService / Ping     : " << request_->message() << std::endl
                  << std::endl;

        // create response
        response_->set_answer("PONG");
    }
};

/**
 * @brief main entry
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char **argv)
{
    // initialize eCAL API
    eCAL::Initialize(argc, argv, "ping server");

    // create Ping service server
    std::shared_ptr<PingService> ping_service = std::make_shared<PingServiceImpl>();
    eCAL::protobuf::CServiceServer<PingService> ping_server(ping_service, "ping service");

    while (eCAL::Ok())
    {
        // sleep 100 ms
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    // finalize eCAL API
    eCAL::Finalize();

    return (0);
}