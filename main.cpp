#include <iostream>
#include <opencv2/opencv.hpp>
#include <cost.h>
#include <match.h>
int main() {
    cv::Mat left=cv::imread("../image/view1.png");
    cv::Mat right=cv::imread("../image/view5.png");

    match DpMatch(left,right,3);
    cv::Mat disparity=DpMatch.compute();
    cv::Mat out, out2;
    cv::normalize(disparity, out, 0, 255, cv::NORM_MINMAX, CV_8UC1);
    cv::namedWindow("disparity");
    cv::imshow("disparity", out);
    cv::imwrite("../image/result.png",out);
    cv::waitKey(0);










}