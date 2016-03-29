//
// Created by tipakorng on 3/18/16.
//

#include "ros/ros.h"
#include "ros/package.h"
#include "matlab_demo/DotProduct.h"
#include "engine.h"

engine *ep_;

bool dotProduct(matlab_demo::DotProduct::Request &request, matlab_demo::DotProduct::Response &response) {

    // Check dimension of vector a and b
    if (request.a.size() != request.b.size()){
        ROS_ERROR("Vectors must have the same number of elements");
    }

    // Initialize Matlab mxArrays
    int vectorSize = request.a.size();
    mxArray *a = mxCreateDoubleMatrix(vectorSize, 1, mxREAL);
    mxArray *b = mxCreateDoubleMatrix(vectorSize, 1, mxREAL);
    std::copy(request.a.begin(), request.a.end(), mxGetPr(a));
    std::copy(request.b.begin(), request.b.end(), mxGetPr(b));
    engPutVariable(ep_, "a", a);
    engPutVariable(ep_, "b", b);
    // Calculate dot product
    engEvalString(ep_, "x = dot_product(a, b)");
    // Retrieve answer
    mxArray *x = engGetVariable(ep_, "x");
    response.x = *reinterpret_cast<double*>(mxGetData(x));
    ROS_INFO("sending back response: [%f]", response.x);
    return true;
}

int main(int argc, char **argv) {
    // Initialize node handle
    ros::init(argc, argv, "dot_product_server");
    ros::NodeHandle nh;

    // Start Matlab engine
    ep_ = engOpen("\0");
    std::string changeDir = "cd " + ros::package::getPath("matlab_demo") + "/matlab";
    engEvalString(ep_, changeDir.c_str());

    // Advertise service
    ros::ServiceServer service = nh.advertiseService("dot_product", dotProduct);
    ROS_INFO("Dot product server is initialized");
    ros::spin();

    return 0;
}
