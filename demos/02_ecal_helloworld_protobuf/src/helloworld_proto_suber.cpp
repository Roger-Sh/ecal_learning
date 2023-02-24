#include <ecal/ecal.h>
#include <ecal/msg/protobuf/subscriber.h>

#include <iostream>
#include <thread>

#include "hello_world.pb.h"

/**
 * @brief single thread callback of subscriber
 * time-consuming process will block other subscriber callback or main thread
 * in this example only this callback will receive data
 * @param hello_world_msg 
 */
void HelloWorldCallback(const proto_messages::HelloWorld &hello_world_msg)
{
    std::cout << "suber1 get data \n"
        << hello_world_msg.name() << " sent a message with ID "
        << hello_world_msg.id() << ":" << std::endl
        << hello_world_msg.msg() << std::endl
        << std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(5000));

}

void HelloWorldCallback2(const proto_messages::HelloWorld &hello_world_msg)
{
    std::cout << "suber2 get data\n"
        << hello_world_msg.name() << " sent a message with ID "
        << hello_world_msg.id() << ":" << std::endl
        << hello_world_msg.msg() << std::endl
        << std::endl;
    // std::this_thread::sleep_for(std::chrono::milliseconds(2000));

}

int main(int argc, char **argv)
{
    // Initialize eCAL and create a protobuf subscriber
    eCAL::Initialize(argc, argv, "Hello World Protobuf Subscriber");
    eCAL::protobuf::CSubscriber<proto_messages::HelloWorld> subscriber("hello_world_protobuf");
    eCAL::protobuf::CSubscriber<proto_messages::HelloWorld> subscriber2("hello_world_protobuf2");

    // Set the Callback
    subscriber.AddReceiveCallback(std::bind(&HelloWorldCallback, std::placeholders::_2));
    subscriber2.AddReceiveCallback(std::bind(&HelloWorldCallback2, std::placeholders::_2));

    // Just don't exit
    int i = 0;
    while (eCAL::Ok())
    {
        // sleep for 2000 ms
        std::cout << "while loop count: " << i++ << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(10000));
    }

    // finalize eCAL API
    eCAL::Finalize();
}