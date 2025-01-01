#include <opencv2/opencv.hpp>

using namespace cv;

Mat histogram_equalize(Mat m){
    Mat r;
    equalizeHist(m,r);
    return r;
}

Mat clahe(Mat m){
    static Ptr<CLAHE> c = createCLAHE(4,Size(8,8));
    Mat r;
    c->apply(m,r);
    return r;
}
