#include <forward_list>
#include<iostream>
#include <opencv2/opencv.hpp>
#include"data_IO/image_IO.hpp"
#include"image_processing/preprocessing/contrast_enhancement.hpp"
#include<opencv2/ximgproc.hpp>
#include"biometrics/feature_extraction.hpp"

using namespace std;

using namespace cv;

const char* img_path = "/home/kosenko/Downloads/DB1_B/101_1.tif";

int main(){
    Mat img = load_tiff(img_path);

    Mat img_he = histogram_equalize(img);
    
    Mat img_clahe = clahe(img);
    
    Mat img_b;
    threshold(img_clahe, img_b, 0, 255, THRESH_BINARY_INV | THRESH_OTSU);
    
    Mat img_t;
    ximgproc::thinning(img_b, img_t, ximgproc::THINNING_ZHANGSUEN);

    imwrite("img.png", img_t);

    forward_list<fingerprint_feature> minutia = extract_features(img_t);
    Mat img_minutia;
    cvtColor(img_t, img_minutia, COLOR_GRAY2BGR);
    Vec3b red = {255,0,0};
    Vec3b green = {0,255,0};
    for(auto i=minutia.begin(); i!=minutia.end(); i++){
        //std::cout << i->type << i->x << i->y;
        img_minutia.at<Vec3b>(i->x,i->y) = i->type == RIDGE_ENDING? red: green;
    }
    imwrite("img_minutia.png", img_minutia);
}
