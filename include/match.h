#ifndef STEREO_MATCH_MATCH_H
#define STEREO_MATCH_MATCH_H

#include <cost.h>
class match{
public:
    match(cv::Mat left,cv::Mat right,int blocksize);
    ~match();
    //视差空间计算
    cv::Mat disparitySpace(int y);

    //计算视差
    cv::Mat compute();

    //匹配代价
    cost* match_cost;

    //核大小
    int blocksize;

    //图像的大小
    cv::Size imagesize;
};
#endif //STEREO_MATCH_MATCH_H
