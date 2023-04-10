#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;


void showHistogram(const string& name, int* hist, const int  hist_cols, const int hist_height){

    Mat imgHist(hist_height, hist_cols, CV_8UC3, CV_RGB(255, 255, 255));// constructs a white image
    //computes histogram maximum
    int max_hist = 0;
    for(int i = 0; i<hist_cols; i++)
        if(hist[i]> max_hist)
            max_hist = hist[i];
    double scale = 1.0;
    scale = (double)hist_height / max_hist;
    int baseline = hist_height - 1;
    for(int x = 0; x < hist_cols; x++){
        Point p1 = Point(x, baseline);
        Point p2 = Point(x, baseline - cvRound(hist[x]* scale));
        line(imgHist, p1, p2, CV_RGB(255, 0, 255));// histogram bins
        // colored in magenta
    }
    imshow(name, imgHist);

}

int main() {

    Mat_<uchar> image = imread("/Users/tonynecula/Faculta/Image Processing/utils/saturn.bmp", IMREAD_GRAYSCALE);
    if(image.empty()) {
        cout << "Failed to load image" << endl;
        return -1;
    }
    imshow("Color Image", image);
    waitKey(0);
    return 0;
}