//
// Created by tipakorng on 3/18/16.
//

#include "ros/ros.h"
#include "matlab_demo/DotProduct.h"

int main(int argc, char **argv) {
    // Init node
    ros::init(argc, argv, "dot_product_client");
    ros::NodeHandle nh;
    ros::ServiceClient client = nh.serviceClient<matlab_demo::DotProduct>("dot_product");

    // Define vectors
    double a[3] = {1, 2, 3};
    double b[3] = {4, 5 ,6};

    // Put array in service
    matlab_demo::DotProduct srv;
    srv.request.a.insert(srv.request.a.end(), a, a+3);
    srv.request.b.insert(srv.request.b.end(), b, b+3);

    if (client.call(srv)) {
        ROS_INFO("dot product = %f", srv.response.x);
    }

    else {
        ROS_ERROR("Something went wrong...");
        return 1;
    }

    return 0;
}