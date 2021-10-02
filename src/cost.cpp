#include <cost.h>
cost::cost(cv::Mat &_left,cv::Mat &_right,int _blocksize)
{
    left=_left;
    right=_right;
    assert(left.size()==right.size());
    blocksize=_blocksize;
    margin=blocksize/2;
}
double cost::aggregate(int x1, int x2, int y)
{
    double sum=0;
    for(int i=y-margin;i<=y+margin;i++)
    {
        for(int j=-margin; j <=margin; j++)
        {
            double l_r=left.at<cv::Vec3b>(i,x1 + j)[0];
            double l_g=left.at<cv::Vec3b>(i,x1 + j)[1];
            double l_b=left.at<cv::Vec3b>(i,x1 + j)[2];

            double r_r=right.at<cv::Vec3b>(i,x2 + j)[0];
            double r_g=right.at<cv::Vec3b>(i,x2 + j)[1];
            double r_b=right.at<cv::Vec3b>(i,x2 + j)[2];
            sum+=std::sqrt(std::pow(l_r-r_r,2)+std::pow(l_b-r_b,2)+std::pow(l_g-r_g,2));
        }
    }
    //normalize
    return sum/std::sqrt(255*255 + 255*255+255*255);
}


