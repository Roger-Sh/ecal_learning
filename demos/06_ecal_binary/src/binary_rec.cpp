#include <ecal/ecal.h>

#include <iostream>
#include <sstream>
#include <chrono>
#include <thread>

// subscriber callback function
void OnReceive(const char * /*topic_name_*/, const struct eCAL::SReceiveCallbackData *data_)
{
    if (data_->size < 1)
        return;

    int content(static_cast<int>(static_cast<unsigned char *>(data_->buf)[0]));
    std::cout << "----------------------------------------------" << std::endl;
    std::cout << " Received binary buffer " << content << std::endl;
    std::cout << "----------------------------------------------" << std::endl;
    std::cout << " Size         : " << data_->size << std::endl;
    std::cout << " Id           : " << data_->id << std::endl;
    std::cout << " Time         : " << data_->time << std::endl;
    std::cout << " Clock        : " << data_->clock << std::endl;
    std::cout << std::endl;
}

int main(int argc, char **argv)
{
    // initialize eCAL API
    eCAL::Initialize(argc, argv, "binary_rec_cb");

    // subscriber for topic "blob"
    eCAL::CSubscriber sub("blob");

    // assign callback
    sub.AddReceiveCallback(OnReceive);

    // idle main loop
    while (eCAL::Ok())
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

    // finalize eCAL API
    eCAL::Finalize();

    return (0);
}