#include"feature_extraction.hpp"
#include<forward_list>
//#include <opencv2/core/hal/interface.h>

using namespace std;
using namespace cv;

forward_list<fingerprint_feature> extract_features(Mat m){
    forward_list<fingerprint_feature> r;
    for(int i=1; i<m.rows-1; i++){
        for(int j=1; j<m.cols-1; j++){
            if(m.at<uchar>(i,j)){
                int cn=0;
                int p[2] = {-1,-1};
                for(int k=0;k<8;k++){
                    uchar pr = m.at<uchar>(i+p[0],j+p[1]);
                    p[k%4/2]+=1-k/4*2;
                    cn+=!pr && m.at<uchar>(i+p[0],j+p[1]);
                }
                if(cn==1) r.push_front({RIDGE_ENDING, i, j});
                else if(cn==3) r.push_front({RIDGE_BIFURCATION, i, j});
            }
        }
    }
    return r;
}
