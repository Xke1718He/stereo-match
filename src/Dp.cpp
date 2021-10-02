#include <Dp.h>
#include <opencv2/opencv.hpp>
void Dp::preCalc(cv::Mat &matrix, cv::Mat &sum, cv::Mat &dirs) {
    sum = cv::Mat::zeros(matrix.rows, matrix.cols, matrix.type());         // not initialized with zero, should not be a problem,
    dirs = cv::Mat::zeros(matrix.rows, matrix.cols, CV_16U);               // because traversion is pre initialized with borders

    int rowEnd=matrix.rows-1;
    int colEnd=matrix.cols-1;

    sum.at<float>(rowEnd,colEnd)=matrix.at<float>(rowEnd,colEnd);

    for(int i=rowEnd-1;i>=0;i--)
    {
        sum.at<float>(i,colEnd)=matrix.at<float>(i,colEnd)+sum.at<float>(i+1,colEnd);
        dirs.at<ushort>(i, colEnd) = 1;
    }
    for(int j=colEnd-1;j>=0;j--)
    {
        sum.at<float>(rowEnd,j)=matrix.at<float>(rowEnd,j)+sum.at<float>(rowEnd,j+1);
        dirs.at<ushort>(rowEnd, j) = 3;
    }
    for(int y=rowEnd-1;y>=0;y--)
    {
        for(int x=colEnd-1;x>=0;x--)
        {
            float s=sum.at<float>(y+1,x);
            float se=sum.at<float>(y+1,x+1);
            float e=sum.at<float>(y,x+1);

            float p=std::min(s,std::min(e,se));
            sum.at<float>(y,x)=p+matrix.at<float>(y,x);
            if(p==s) dirs.at<ushort>(y,x)=1;
            if(p==se) dirs.at<ushort>(y,x)=2;
            if(p==e) dirs.at<ushort>(y,x)=3;
        }
    }
}
void Dp::disparityFromDirs(cv::Mat &sum, cv::Mat &dirs, cv::Mat &disp, int line, int offset) {
    assert(dirs.type() == CV_16U);

    // wir bekommen jetzt einen index x, y
    int rowLast = dirs.rows - 1;
    int colLast = dirs.cols - 1;

    int lastval = -1;
    int x1 = 0;
    int x2 = 0;


    float minVal = std::numeric_limits<float>::max();
    int minIndex = 0;
    // seek top entry
    for(x2 = 0; x2 < sum.cols; ++x2) {
        float val = sum.at<float>(x1, x2);
        if(val > minVal) {
            minIndex = x2;
            minVal = val;
        }
    }
    x2 = minIndex;


    // safe x1, x2 as disparity match
    ushort disparity = abs(x2 - x1);
    ushort* disp_ptr = disp.ptr<ushort>(line);

    disp_ptr[x1 + offset] = disparity;

    while(x1 < rowLast && x2 < colLast) {
        ushort d = dirs.at<ushort>(x1, x2);
        if(d == 1) {    // 1 = down, skipping left index, left got occloded (occlusion from right)
            x1++;
            if(lastval >= 0) disp_ptr[x1 + offset] = lastval;   // dips[line, x1 + offset] = lastval
            //disp_ptr[x1 + offset] = 0;
        }
        if(d == 2) { // match
            // next entry will be match
            x1++;
            x2++;
            disparity = abs(x2 - x1);

            disp_ptr[x1 + offset] = disparity;
            lastval = disparity;
        }
        if(d == 3) { // 2 = right, skipping right index, occlusion don't care..
            x2++;
            if(lastval >= 0) disp_ptr[x1 + offset] = lastval;   // dips[line, x1 + offset] = lastval
            //disp_ptr[x1 + offset]= 0;
        }
    }
}

Dp::Dp() {

}
