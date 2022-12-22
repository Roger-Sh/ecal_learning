#include <ecal/ecal.h>

#include <algorithm>
#include <iostream>

int main(int argc, char **argv)
{
    // initialize eCAL API
    eCAL::Initialize(argc, argv, "binary_snd");

    // publisher for topic "blob"
    eCAL::CPublisher pub("blob");

    // create binary buffer
    std::vector<unsigned char> bin_buffer(1024);

    // send updates
    unsigned char cnt = 0;
    while (eCAL::Ok())
    {
        // fill buffer
        std::fill(bin_buffer.begin(), bin_buffer.end(), cnt);

        // send buffer
        pub.Send(bin_buffer.data(), bin_buffer.size());
        std::cout << "Sent buffer filled with " << static_cast<int>(cnt) << std::endl;

        // sleep 100 ms
        eCAL::Process::SleepMS(1000);

        cnt++;
    }

    // finalize eCAL API
    eCAL::Finalize();

    return (0);
}