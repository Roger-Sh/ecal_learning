#include <ecal/ecal.h>
#include <ecal/msg/protobuf/client.h>

#include <iostream>
#include <chrono>
#include <thread>
#include <sstream>

#include "math_service.pb.h"

/**
 * @brief callback for math service response
 *
 * @param service_response_
 */
void OnMathResponse(const struct eCAL::SServiceInfo& service_info_, const std::string& response_)
{
    std::stringstream ss;
    ss << "OnServiceResponse get response: \n";
    ss << "service_info_.call_state" << service_info_.call_state << "\n";
    ss << "service_info_.error_msg" << service_info_.error_msg << "\n";
    ss << "service_info_.host_name" << service_info_.host_name << "\n";
    ss << "service_info_.method_name" << service_info_.method_name << "\n";
    ss << "service_info_.ret_state" << service_info_.ret_state << "\n";
    ss << "service_info_.service_name" << service_info_.service_name << "\n";
    math_service_pb::SFloat response_proto;
    response_proto.ParseFromString(response_);
    ss << "response: " << response_proto.out();

    std::cout << ss.str();

    // std::this_thread::sleep_for(std::chrono::milliseconds(5000));
}

// main entry
int main(int argc, char **argv)
{
    // initialize eCAL API
    eCAL::Initialize(argc, argv, "math client");

    // create math service client
    eCAL::protobuf::CServiceClient<math_service_pb::MathService> math_client;

    // add response callback
    math_client.AddResponseCallback(OnMathResponse);

    // loop variables
    int inp1(0);
    int inp2(0);

    while (eCAL::Ok())
    {
        //////////////////////////////////////
        // Math service (callback variant)
        //////////////////////////////////////
        math_service_pb::SFloatTuple math_request;
        math_request.set_inp1(inp1++);
        math_request.set_inp2(inp2++);

        std::cout << std::endl
                    << "Calling MathService::Add method with      : " << math_request.inp1() << " and " << math_request.inp1() << std::endl;
        if (!math_client.Call("Add", math_request))
        {
            std::cout << "MathService::Add method call failed .." << std::endl
                        << std::endl;
        }

        std::cout << std::endl
                    << "Calling MathService::Multiply method with : " << math_request.inp1() << " and " << math_request.inp1() << std::endl;
        if (!math_client.Call("Multiply", math_request))
        {
            std::cout << "MathService::Multiply method call failed .." << std::endl
                        << std::endl;
        }

        std::cout << std::endl
                    << "Calling MathService::Divide method with   : " << math_request.inp1() << " and " << math_request.inp1() << std::endl;
        if (!math_client.Call("Divide", math_request))
        {
            std::cout << "MathService::Divide method call failed .." << std::endl
                        << std::endl;
        }

        // sleep a second
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    // finalize eCAL API
    eCAL::Finalize();

    return (0);
}