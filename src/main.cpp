#include <forward_list>
#include<iostream>
#include <opencv2/opencv.hpp>
#include"data_IO/image_IO.hpp"
#include"image_processing/preprocessing/contrast_enhancement.hpp"
#include<opencv2/ximgproc.hpp>
#include"biometrics/feature_extraction.hpp"
#include<filesystem>
#include<chrono>


using namespace std;

using namespace cv;

const char* img_path = "/home/kosenko/Downloads/DB1_B/101_1.tif";

const char* dataset_path = "/home/kosenko/Downloads/DB1_B/";

#define duration_s(x) chrono::duration_cast<chrono::duration<float>>(x).count()

const char* t_names[] = {"read", "histogram equalization", "CLAHE", "binarization", "thinning", "feature extraction"};

int main(){
    const int tn = 7;
    double t_avg[tn-1];
    for(int i=0; i<tn-1; i++)t_avg[i]=0;
    int i_n=0;
    for(const auto &entry:filesystem::directory_iterator{dataset_path}){
        auto t0 = chrono::high_resolution_clock::now();
        Mat img = load_tiff(entry.path().c_str());
        auto t1 = chrono::high_resolution_clock::now();
        Mat img_he = histogram_equalize(img);
        auto t2 = chrono::high_resolution_clock::now();
        
        Mat img_clahe = clahe(img);
        auto t3 = chrono::high_resolution_clock::now();
        
        Mat img_b;
        threshold(img_clahe, img_b, 0, 255, THRESH_BINARY_INV | THRESH_OTSU);
        auto t4 = chrono::high_resolution_clock::now();
        
        Mat img_t;
        ximgproc::thinning(img_b, img_t, ximgproc::THINNING_ZHANGSUEN);
        auto t5 = chrono::high_resolution_clock::now();

        //imwrite("img.png", img_t);

        forward_list<fingerprint_feature> minutia = extract_features(img_t);
        auto t6 = chrono::high_resolution_clock::now();
        //Mat img_minutia;
        /*
        cvtColor(img_t, img_minutia, COLOR_GRAY2BGR);
        Vec3b red = {255,0,0};
        Vec3b green = {0,255,0};
        for(auto i=minutia.begin(); i!=minutia.end(); i++){
            //std::cout << i->type << i->x << i->y;
            img_minutia.at<Vec3b>(i->x,i->y) = i->type == RIDGE_ENDING? red: green;
        }*/
        //imwrite("img_minutia.png", img_minutia);
        img.release();
        img_b.release();
        img_clahe.release();
        img_he.release();
        img_t.release();

        typeof(t0) ta[] = {t0,t1,t2,t3,t4,t5,t6};
        for(int i=0; i<tn-1; i++){
            double t = duration_s(ta[i+1]-ta[i]);
            t_avg[i]+=t;
        }
        i_n++;
    }
    cout <<"average over "<<i_n<<" images:\n\n";
    for(int i=0; i<tn-1; i++){
        cout <<t_names[i]<<' '<<t_avg[i]/i_n*1000<<"ms\n";
    }
}
