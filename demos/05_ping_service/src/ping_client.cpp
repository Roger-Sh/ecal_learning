#include <ecal/ecal.h>
#include <ecal/msg/protobuf/client.h>

#include <iostream>
#include <chrono>
#include <thread>
#include <sstream>

#include "ping_service.pb.h"

/**
 * @brief callback of service client ping
 * 
 * @param service_info_ 
 * @param response_ 
 */
void OnPingResponse(const struct eCAL::SServiceInfo& service_info_, const std::string& response_)
{
    std::stringstream ss;
    ss << "OnServiceResponse get response: \n";
    ss << "service_info_.call_state" << service_info_.call_state << "\n";
    ss << "service_info_.error_msg" << service_info_.error_msg << "\n";
    ss << "service_info_.host_name" << service_info_.host_name << "\n";
    ss << "service_info_.method_name" << service_info_.method_name << "\n";
    ss << "service_info_.ret_state" << service_info_.ret_state << "\n";
    ss << "service_info_.service_name" << service_info_.service_name << "\n";
    PingResponse response_proto;
    response_proto.ParseFromString(response_);
    ss << "response: " << response_proto.answer() << "\n";

    std::cout << ss.str();

    // std::this_thread::sleep_for(std::chrono::milliseconds(5000));
}

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
    eCAL::Initialize(argc, argv, "ping client");

    // create ping service client
    eCAL::protobuf::CServiceClient<PingService> ping_client;
    ping_client.AddResponseCallback(OnPingResponse);

    // sleep a second for serivce connection
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    while (eCAL::Ok())
    {
        PingRequest ping_req_proto;
        ping_req_proto.set_message("ping!");

        if (!ping_client.Call("Ping", ping_req_proto))
        {
            std::cout << "ping call failed\n";
        }

        // sleep a second
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    // finalize eCAL API
    eCAL::Finalize();

    return (0);
}