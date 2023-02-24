#include <ecal/ecal.h>

#include <iostream>
#include <chrono>
#include <thread>
#include <sstream>

// main entry
int main(int argc, char **argv)
{
    // initialize eCAL API
    eCAL::Initialize(argc, argv, "minimal client");

    // create minimal service client
    eCAL::CServiceClient minimal_client("minimal_service");
    // minimal_client.AddResponseCallback(OnServiceResponse);

    while (eCAL::Ok())
    {
        // Service call (blocking)
        std::string host_name("");
        std::string method_name("echo");
        std::string request("Hello");
        eCAL::SServiceInfo service_info;
        std::string response;
        minimal_client.Call(host_name, method_name, request, service_info, response);

        std::stringstream ss;
        ss << "response: " << response << "\n";
        ss << "service_info.call_state: " << service_info.call_state << "\n";
        ss << "service_info.error_msg: " << service_info.error_msg << "\n";
        ss << "service_info.host_name: " << service_info.host_name << "\n";
        ss << "service_info.method_name: " << service_info.method_name << "\n";
        ss << "service_info.ret_state: " << service_info.ret_state << "\n";
        ss << "service_info.service_name: " << service_info.service_name << "\n";
        std::cout << ss.str();

        // sleep a second
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    // finalize eCAL API
    eCAL::Finalize();

    return (0);
}
