#include <opencv2/imgcodecs.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;

Mat load_tiff(const char* path){
    Mat image = imread(path,IMREAD_GRAYSCALE);
    return image;
}
