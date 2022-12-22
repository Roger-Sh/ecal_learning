#include <ecal/ecal.h>
#include <ecal/msg/protobuf/client.h>

#include <iostream>
#include <chrono>
#include <thread>

#include "ping_service.pb.h"

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
    eCAL::protobuf::CServiceClient<PingService> ping_client("ping service");

    // waiting for service
    while (!ping_client.IsConnected())
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        std::cout << "Waiting for the service .." << std::endl;
    }

    while (eCAL::Ok())
    {
        if (ping_client.IsConnected())
        {
            //////////////////////////////////////
            // Ping service (blocking call)
            //////////////////////////////////////
            PingRequest ping_request;
            ping_request.set_message("PING");
            eCAL::ServiceResponseVecT service_response_vec;
            if (ping_client.Call("Ping", ping_request, -1, &service_response_vec))
            {
                std::cout << std::endl
                          << "PingService::Ping method called with message : " << ping_request.message() << std::endl;

                for (auto service_response : service_response_vec)
                {
                    switch (service_response.call_state)
                    {
                        // service successful executed
                        case call_state_executed:
                        {
                            PingResponse ping_response;
                            ping_response.ParseFromString(service_response.response);
                            std::cout << "Received response PingService / Ping : " << ping_response.answer() << " from host " << service_response.host_name << std::endl;
                            break;
                        }

                        // service execution failed
                        case call_state_failed:
                        {
                            std::cout << "Received error PingService / Ping : " << service_response.error_msg << " from host " << service_response.host_name << std::endl;
                            break;
                        }

                        default:
                        {
                            break;
                        }
                    }
                }
            }
            else
            {
                std::cout << "PingService::Ping method call failed .." << std::endl
                          << std::endl;
            }
        }

        // sleep a second
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    // finalize eCAL API
    eCAL::Finalize();

    return (0);
}