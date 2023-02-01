// ecal
#include <ecal/ecal.h>
#include <ecal/msg/protobuf/publisher.h>

// pcl
#include <pcl/common/common.h>
#include <pcl/point_types.h>

// std
#include <iostream>
#include <thread>

// protobuf
#include "pcl_pointcloud_xyz.pb.h"

/**
 * @brief pub PCL PointCloud as Protobuf msg
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char **argv)
{
    int n = 1;
    std::cout << n << std::endl;
    n++;

    // init ecal
    eCAL::Initialize(argc, argv, "pcl_pc_puber");

    // init ecal publisher
    eCAL::protobuf::CPublisher<pcl_proto_msgs::pointcloud_xyz> publisher("pcl_pc_xyz");

    // create cloud
    pcl::PointCloud<pcl::PointXYZ> cloud;
    cloud.width = 100;
    cloud.height = 1;
    cloud.is_dense = false;
    cloud.resize(cloud.width * cloud.height);
    for (auto &point : cloud)
    {
        point.x = 10.0 * rand() / (RAND_MAX + 1.0f);
        point.y = 10.0 * rand() / (RAND_MAX + 1.0f);
        point.z = 5.0 * rand() / (RAND_MAX + 1.0f);
    }

    // pub pcl pointcloud
    size_t id = 0;
    float move_bias = 0.2;
    int move_length = 50;
    while (eCAL::Ok())
    {
        // update cloud in every loop
        if ((int)id%move_length == 0)
        {
            move_bias = move_bias * -1.0;
        }
        for (auto &point : cloud)
        {

            point.x += move_bias;
        }

        // serialize cloud data to pc_xyz_proto
        pcl_proto_msgs::pointcloud_xyz pcl_pc_xyz_proto_msg;
        pcl_pc_xyz_proto_msg.set_id(id);
        pcl_pc_xyz_proto_msg.set_width(cloud.width);
        pcl_pc_xyz_proto_msg.set_height(cloud.height);
        pcl_pc_xyz_proto_msg.set_is_dense(cloud.is_dense);
        pcl_pc_xyz_proto_msg.set_points_size(cloud.points.size());
        pcl_pc_xyz_proto_msg.set_points_data(cloud.points.data(), cloud.points.size()*sizeof(pcl::PointXYZ));
        std::cout << "sizeof(pcl::PointXYZ): " << sizeof(pcl::PointXYZ) << std::endl;

        // pub protobuf msg
        publisher.Send(pcl_pc_xyz_proto_msg);
        std::cout << "sent msg " << id << std::endl;
        id++;
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    // end ecal
    eCAL::Finalize();

    return 0;
}