#include <ros/ros.h>
#include <apriltags/AprilTagDetections.h>
#include "ApriltagsClass.hpp"
#include <Eigen/Dense>
#include <fstream>
#include "cat_tabletag_detection/GetTagPose.h"

#define TABLE_TAG_ID 127

ApriltagsClass ctag;


// get table tag pose
void gettableTagPose(Eigen::Vector4d &tag_pos){

    ctag.init_noIDinput();

    geometry_msgs::PoseStamped tag_pose;
    ctag.getTagPoseByRequest(TABLE_TAG_ID, tag_pose);

    while(!ctag.checkGivenTagStability(TABLE_TAG_ID, tag_pose)){
        ctag.getTagPoseByRequest(TABLE_TAG_ID, tag_pose);
    }

    std::cout << "TAG ID : " << TABLE_TAG_ID << std::endl;
    std::cout << "tag_pose : " << tag_pose << std::endl;

    tag_pos << tag_pose.pose.position.x , tag_pose.pose.position.y , tag_pose.pose.position.z , 1.0;

}



int main(int argc, char** argv){

    //init ros, subscribers, publishers and services
    ros::init(argc, argv, "tabletag");

    ros::NodeHandle nh;

    Eigen::Vector4d tag_pos;

    gettableTagPose(tag_pos);

    std::cout << "tag_pos : " << tag_pos << std::endl;
}
