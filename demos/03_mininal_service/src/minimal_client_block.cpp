#include <ecal/ecal.h>

#include <iostream>
#include <chrono>
#include <thread>

// callback for service response
// void OnServiceResponse(const struct eCAL::SServiceResponse &service_response_)
// {
//     std::this_thread::sleep_for(std::chrono::milliseconds(10000));

//     switch (service_response_.call_state)
//     {
//         // service successful executed
//         case eCallState::call_state_executed:
//             std::cout << "Received response for method in CB " 
//                 << service_response_.method_name << " : " 
//                 << service_response_.response 
//                 << " from host " << service_response_.host_name << std::endl;
//             break;

//         // service execution failed
//         case eCallState::call_state_failed:
//             std::cout << "Received error for method in CB " 
//                 << service_response_.method_name << " : " 
//                 << service_response_.error_msg 
//                 << " from host " << service_response_.host_name << std::endl;
//             break;

//         default:
//             break;
//     }
// }

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
        // eCAL::SServiceResponse service_info;
        std::string method_name("echo");
        std::string request("Hello");

        //////////////////////////////////////
        // Service call (blocking)
        //////////////////////////////////////
        eCAL::ServiceResponseVecT service_response_vec;
        if (minimal_client.Call(method_name, request, -1, &service_response_vec))
        {
            for (auto service_response : service_response_vec)
            {
                std::cout << "Method 'echo' called with message in blocking : " << request << std::endl;

                switch (service_response.call_state)
                {
                    // service successful executed
                    case eCallState::call_state_executed:
                        std::cout << "Received response in blocking: " 
                            << service_response.response 
                            << " from host " << service_response.host_name << std::endl;
                        break;
                    // service execution failed
                    
                    case eCallState::call_state_failed:
                        std::cout << "Received error in blocking: " 
                            << service_response.error_msg 
                            << " from host " << service_response.host_name << std::endl;
                        break;
                    
                    default:
                        std::cout << "service_info.call_state in blocking: " << service_response.call_state << "\n";
                        break;
                }
            }
        }
        else
        {
            std::cout << "Method blocking call failed .." << std::endl
                << std::endl;
        }

        // sleep a second
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    // finalize eCAL API
    eCAL::Finalize();

    return (0);
}
