// ecal
#include <ecal/ecal.h>
#include <ecal/msg/protobuf/subscriber.h>

// pcl
#include <pcl/common/common.h>
#include <pcl/point_types.h>
#include <pcl/visualization/pcl_visualizer.h>

// std
#include <iostream>
#include <thread>

// protobuf
#include "pcl_pointcloud_xyz.pb.h" 

// global cloud
pcl::PointCloud<pcl::PointXYZ> cloud;

/**
 * @brief callback of subscriber for pcl_pc_xyz_proto_msg
 * 
 * @param pcl_pc_xyz_proto_msg 
 */
void pcl_pc_xyz_CB(const pcl_proto_msgs::pointcloud_xyz &pcl_pc_xyz_proto_msg)
{
    // deserialize pc_xyz_proto to cloud data
    // cloud.points.clear();
    cloud.height = pcl_pc_xyz_proto_msg.height();
    cloud.width = pcl_pc_xyz_proto_msg.width();
    cloud.is_dense = pcl_pc_xyz_proto_msg.is_dense();
    cloud.points.resize(pcl_pc_xyz_proto_msg.points_size());
    std::memcpy(cloud.points.data(), pcl_pc_xyz_proto_msg.points_data().data(), cloud.points.size()*sizeof(pcl::PointXYZ));
}

/**
 * @brief subscribe PCL PointCloud as Protobuf msg
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char **argv)
{
    // init ecal
    eCAL::Initialize(argc, argv, "pcl_pc_suber");

    // create ecal protobuf subscriber
    eCAL::protobuf::CSubscriber<pcl_proto_msgs::pointcloud_xyz> subscriber("pcl_pc_xyz");

    // set callback
    subscriber.AddReceiveCallback(std::bind(&pcl_pc_xyz_CB, std::placeholders::_2));

    // set viewer
    pcl::visualization::PCLVisualizer viewer("cloud");
    pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> cloud_color_handler(cloud.makeShared(), 255, 255, 255);
    viewer.addPointCloud(cloud.makeShared(), cloud_color_handler, "cloud");
    viewer.addCoordinateSystem(1.0, "cloud", 0);
    viewer.setBackgroundColor(0.05, 0.05, 0.05, 0); // Setting background to a dark grey
    viewer.setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 2, "cloud");

    // ecal loop
    while (eCAL::Ok() && !viewer.wasStopped())
    {
        pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> cloud_color_handler(cloud.makeShared(), 255, 255, 255);
        viewer.updatePointCloud(cloud.makeShared(), cloud_color_handler, "cloud");
        viewer.spinOnce();
    }

    // finalize eCAL API
    eCAL::Finalize();

    return 0;
}