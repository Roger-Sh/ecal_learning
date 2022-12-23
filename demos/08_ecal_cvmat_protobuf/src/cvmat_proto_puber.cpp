// ecal
#include <ecal/ecal.h>
#include <ecal/msg/protobuf/publisher.h>

// opencv
#include <opencv2/opencv.hpp>

// std
#include <iostream>
#include <thread>

// protobuf
#include "cvmat.pb.h"

/**
 * @brief ecal publisher
 * pub cv image as protobuf msg 
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char **argv)
{
    // init ecal
    eCAL::Initialize(argc, argv, "cvmat_proto_puber");
    
    // init ecal publisher
    eCAL::protobuf::CPublisher<cvmsgs::cvmat> publisher("cvmat_proto");

    
    // init cv mat
    unsigned int id = 0;
    cv::Mat image_origin = cv::Mat::ones(cv::Size(1280, 720), CV_8UC3);
    cv::Mat image_ID;

    // pub image protobuf msg in every 50ms
    while (eCAL::Ok())
    {
        // update image ID
        image_origin.copyTo(image_ID);
        cv::putText(image_ID, std::to_string(id), cv::Point(100, 100), cv::FONT_HERSHEY_COMPLEX, 1.0, cv::Scalar(250, 250, 250), 1);
        
        // create cvmat protobuf msg object
        cvmsgs::cvmat cvmat_msg;
        cvmat_msg.set_id(id);
        cvmat_msg.set_rows(image_ID.rows);
        cvmat_msg.set_cols(image_ID.cols);
        cvmat_msg.set_elem_type(image_ID.type());
        cvmat_msg.set_elem_size((int)image_ID.elemSize());
        cvmat_msg.set_mat_data(image_ID.data,
            (size_t)(image_ID.rows * image_ID.cols * image_ID.elemSize()));

        // send protobuf msg
        publisher.Send(cvmat_msg);
        std::cout << "sent message " << id << std::endl;
        id++;
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    
    // end ecal
    eCAL::Finalize();

    return 0;
}
