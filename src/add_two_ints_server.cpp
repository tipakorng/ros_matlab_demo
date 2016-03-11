//
// Created by tipakorng on 3/9/16.
//

#include "ros/ros.h"
#include "matlab_example/AddTwoInts.h"
#include "engine.h"

engine *ep_;

bool add(matlab_example::AddTwoInts::Request  &req,
         matlab_example::AddTwoInts::Response &res)
{
    mxArray *a = mxCreateDoubleMatrix(1, 1 , mxREAL);
    mxArray *b = mxCreateDoubleMatrix(1, 1 , mxREAL);
    memcpy(mxGetPr(a), &req.a, sizeof(double));
    memcpy(mxGetPr(b), &req.b, sizeof(double));
    engPutVariable(ep_, "a", a);
    engPutVariable(ep_, "b", b);

    engEvalString(ep_, "sum = add_two_ints(a, b);");

    mxArray *sumMatlab = engGetVariable(ep_, "sum");
    int *sum = reinterpret_cast<int*>(mxGetData(sumMatlab));

    res.sum = *sum;
//    res.sum = req.a + req.b;
    ROS_INFO("request: x=%ld, y=%ld", (long int)req.a, (long int)req.b);
    ROS_INFO("sending back response: [%ld]", (long int)res.sum);
    return true;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "add_two_ints_server");
    ros::NodeHandle n;

    ep_ = engOpen("\0");

    ros::ServiceServer service = n.advertiseService("add_two_ints", add);
    ROS_INFO("Ready to add two ints.");
    ros::spin();

    return 0;
}
