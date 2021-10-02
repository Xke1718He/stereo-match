#include <iostream>
#include <opencv2/opencv.hpp>
#include <utility>

#ifndef STEREO_MATCH_COST_H
#define STEREO_MATCH_COST_H

class cost{
public:
    cost(cv::Mat &_left,cv::Mat &_right,int _blocksize);
    double aggregate(int x1, int x2, int y);
    cv::Mat left;//左图像
    cv::Mat right;//右图像
    int margin;//边界
    int blocksize;//block大小

};
#endif //STEREO_MATCH_COST_H
