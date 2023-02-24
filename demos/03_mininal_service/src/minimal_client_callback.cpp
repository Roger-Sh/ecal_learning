#include <ecal/ecal.h>

#include <iostream>
#include <chrono>
#include <thread>
#include <sstream>

// callback for service response
// 单次调用不会被阻塞
// 连续调用service，如果上一个请求还未结束，则会被阻塞
void OnServiceResponse(const struct eCAL::SServiceInfo& service_info_, const std::string& response_)
{
    std::stringstream ss;
    ss << "OnServiceResponse get response: \n";
    ss << "service_info_.call_state" << service_info_.call_state << "\n";
    ss << "service_info_.error_msg" << service_info_.error_msg << "\n";
    ss << "service_info_.host_name" << service_info_.host_name << "\n";
    ss << "service_info_.method_name" << service_info_.method_name << "\n";
    ss << "service_info_.ret_state" << service_info_.ret_state << "\n";
    ss << "service_info_.service_name" << service_info_.service_name << "\n";
    ss << "response: " << response_;
    std::cout << ss.str();

    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
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

        // first CallAsync no blocking
        // second callAsync will be blocked if the first callAsync is not finished
        std::cout << "start call async. \n";
        minimal_client.CallAsync(method_name, request);
        std::cout << "finish call async. \n";

        // sleep a second
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    // finalize eCAL API
    eCAL::Finalize();

    return (0);
}
