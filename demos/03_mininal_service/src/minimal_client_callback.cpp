#include <ecal/ecal.h>

#include <iostream>
#include <chrono>
#include <thread>

// callback for service response
void OnServiceResponse(const struct eCAL::SServiceResponse &service_response_)
{
    switch (service_response_.call_state)
    {
        // service successful executed
        case eCallState::call_state_executed:
            std::cout << "Received response for method in CB " 
                << service_response_.method_name << " : " 
                << service_response_.response 
                << " from host " << service_response_.host_name << std::endl;
            break;

        // service execution failed
        case eCallState::call_state_failed:
            std::cout << "Received error for method in CB " 
                << service_response_.method_name << " : " 
                << service_response_.error_msg 
                << " from host " << service_response_.host_name << std::endl;
            break;

        default:
            break;
    }
}

// main entry
int main(int argc, char **argv)
{
    // initialize eCAL API
    eCAL::Initialize(argc, argv, "minimal client");

    // create minimal service client
    eCAL::CServiceClient minimal_client("minimal_service");
    minimal_client.AddResponseCallback(OnServiceResponse);

    while (eCAL::Ok())
    {
        // eCAL::SServiceResponse service_info;
        std::string method_name("echo");
        std::string request("Hello");

        // no blocking with callback
        if (minimal_client.Call(method_name, request))
        {
            std::cout << "Method 'echo' called with message in CB: " << request << std::endl;
        }
        else
        {
            std::cout << "Method callback call failed in CB .." << std::endl;
        }

        // sleep a second
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    // finalize eCAL API
    eCAL::Finalize();

    return (0);
}
