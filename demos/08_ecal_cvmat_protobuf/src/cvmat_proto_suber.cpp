// ecal
#include <ecal/ecal.h>
#include <ecal/msg/protobuf/subscriber.h>

// opencv
#include <opencv2/opencv.hpp>

// std
#include <iostream>
#include <thread>

#include "cvmat.pb.h"

/**
 * @brief callback of cvmat protobuf msg subscriber
 * show cv image
 * @param cvmat_proto_msg
 */
void cvmat_proto_CB(const cvmsgs::cvmat &cvmat_proto_msg)
{
    cv::Mat image;

    image.create(
        cvmat_proto_msg.rows(),
        cvmat_proto_msg.cols(),
        cvmat_proto_msg.elem_type());

    size_t data_size = cvmat_proto_msg.rows() * cvmat_proto_msg.cols() * cvmat_proto_msg.elem_size();

    std::copy(
        reinterpret_cast<unsigned char *>(const_cast<char *>(cvmat_proto_msg.mat_data().data())),
        reinterpret_cast<unsigned char *>(const_cast<char *>(cvmat_proto_msg.mat_data().data()) + data_size),
        image.data);

    std::cout << "received image " << cvmat_proto_msg.id() <<std::endl; 
    cv::imshow("image", image);
    cv::waitKey(10);
}

/**
 * @brief ecal cv image protobuf msg subscriber
 *
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char **argv)
{
    // init ecal
    eCAL::Initialize(argc, argv, "cvmat_proto_suber");

    // create ecal protobuf subscriber
    eCAL::protobuf::CSubscriber<cvmsgs::cvmat> subscriber("cvmat_proto");

    // set callback
    subscriber.AddReceiveCallback(std::bind(&cvmat_proto_CB, std::placeholders::_2));

    // ecal loop, just dont't exit the program
    size_t i = 0;
    while (eCAL::Ok())
    {
        // sleep for 2000 ms
        std::cout << "while loop count: " << i++ << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    // finalize eCAL API
    eCAL::Finalize();

    return 0;
}
