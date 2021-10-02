#ifndef STEREO_MATCH_DP_H
#define STEREO_MATCH_DP_H
#include <opencv2/opencv.hpp>
class Dp{
public:
    Dp();
    static void preCalc(cv::Mat &matrix, cv::Mat &sum, cv::Mat &dirs);
    static void disparityFromDirs(cv::Mat &sum, cv::Mat &dirs, cv::Mat &disp, int line, int offset);

};
#endif //STEREO_MATCH_DP_H
