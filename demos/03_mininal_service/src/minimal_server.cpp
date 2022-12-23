#include <ecal/ecal.h>

#include <iostream>
#include <chrono>
#include <thread>

// method callback
int OnMethodCallback(
    const std::string &method_, 
    const std::string & /*req_type_*/, 
    const std::string & /*resp_type_*/, 
    const std::string &request_, 
    std::string &response_)
{
    // check duration of service
    int cnt = 0;
    while(cnt < 10)
    {
        std::cout << "cnt: " << cnt << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        cnt++;
    }


    std::cout << "Method called : " << method_ << std::endl;
    std::cout << "Request       : " << request_ << std::endl
              << std::endl;
    response_ = request_;
    return 42;
}

// main entry
int main(int argc, char **argv)
{
    // initialize eCAL API
    eCAL::Initialize(argc, argv, "minimal server");

    // create minimal service server
    eCAL::CServiceServer minimal_server("minimal_service");

    // add method callback
    minimal_server.AddMethodCallback("echo", "", "", OnMethodCallback);

    // idle
    while (eCAL::Ok())
    {
        // sleep 100 ms
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    // finalize eCAL API
    eCAL::Finalize();

    return (0);
}