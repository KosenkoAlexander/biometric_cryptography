#include<opencv2/opencv.hpp>
#include<forward_list>

using namespace std;
using namespace cv;

typedef enum{
    RIDGE_ENDING,
    RIDGE_BIFURCATION
} fingerprint_feature_type;

typedef struct {
    fingerprint_feature_type type;
    int x,y;
}fingerprint_feature;

forward_list<fingerprint_feature> extract_features(Mat m);
