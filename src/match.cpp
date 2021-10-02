#include <match.h>
#include <Dp.h>
//构造函数
match::match(cv::Mat left,cv::Mat right,int blocksize){
    //初始化代价
    match_cost= new cost(left,right,blocksize);
    this->blocksize=blocksize;
    this->imagesize=left.size();
}
//析构函数
match::~match() {
    delete match_cost;
}
//视差空间的计算
cv::Mat match::disparitySpace(int y)
{
    int margin=blocksize/2;//偏移量 边界
    int start=margin;//起始点
    int end=imagesize.width-margin;//结束点

    //初始化
    cv::Mat map=cv::Mat(end-start,end-start,CV_32F,std::numeric_limits<float>::max());
    for(int x1=start;x1<end;x1++)
    {
        auto* mptr=map.ptr<float>(x1-margin);
        for(int x2=start;x2<end;x2++)
        {
            mptr[x2-margin]= match_cost->aggregate(x1, x2, y);
//            std::cout<<"cost: "<<(double)match_cost->aggregate(x1, x2, y)<<std::endl;
        }
    }
    return map;
}
cv::Mat match::compute() {
    //视差图像初始化
    cv::Mat disparity = cv::Mat::zeros(imagesize.height, imagesize.width, CV_16U);
    //边界
    int margin=blocksize/2;
    //起始位置
    int start=margin;
    //终点位置
    int stopH=imagesize.height-margin;
    int stopW=imagesize.width-margin;

    assert(stopH - start > 0);          // image to small
    assert(stopW - start > 0);          // image to small

    for(int y=start;y<stopH;y++)
    {
        cv::Mat simmap=disparitySpace(y);
        cv::Mat sum, dirs;
        Dp::preCalc(simmap, sum, dirs);
        Dp::disparityFromDirs(sum, dirs, disparity, y, margin);

    }
    return disparity;
}

