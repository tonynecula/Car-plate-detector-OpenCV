#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

typedef struct image_channels_bgr{
    Mat B;
    Mat G;
    Mat R;
};

typedef struct image_channels_hsv{
    Mat H;
    Mat S;
    Mat V;
};
image_channels_bgr break_channels(Mat source){

    /*
     * Create a function that will copy the R, G and B channels of a color,
     * RGB image (CV_8UC3 type) into three matrices of type CV_8UC1 (grayscale images).
     * Return the three matrices in an image_channels_bgr structure
     *
     * Inputs:
     *  source: the source image(BGR)
     * Variables:
     *  rows: number of rows of the source matrix
     *  cols: number of cols of the source matrix
     *  B, G, R: Matrices that will store each a color channel
     *  bgr_channels: structure of type image_channels_bgr that will return three channels
     */

    int rows, cols;
    Mat B, G, R;
    image_channels_bgr bgr_channels;

    rows = source.rows;
    cols = source.cols;

    B.create(rows, cols, CV_8UC1);
    G.create(rows, cols, CV_8UC1);
    R.create(rows, cols, CV_8UC1);

    // Get the three channels
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            Vec3b bgrPixel = source.at<Vec3b>(i, j);
            B.at<uchar>(i, j) = bgrPixel[0];
            G.at<uchar>(i, j) = bgrPixel[1];
            R.at<uchar>(i, j) = bgrPixel[2];
        }
    }

    // Store them in the structure
    bgr_channels.B = B;
    bgr_channels.G = G;
    bgr_channels.R = R;

    return bgr_channels;

}

void display_channels(image_channels_bgr bgr_channels){
    /*
     * Display each channel in a different window
     * Do not put here the waitKey() try to use only one at the end of the lab
     * Input:
     *  bgr_channels: structure of type image_channels_bgr that will store B, G, R channels
     *
     */
    namedWindow("Blue Channel", WINDOW_AUTOSIZE);
    imshow("Blue Channel", bgr_channels.B);
    namedWindow("Green Channel", WINDOW_AUTOSIZE);
    imshow("Green Channel", bgr_channels.G);
    namedWindow("Red Channel", WINDOW_AUTOSIZE);
    imshow("Red Channel", bgr_channels.R);

}

Mat bgr_2_grayscale(Mat source){
    /*
    * Create a function that will convert a color RGB image (CV_8UC3 type) to a grayscale image (CV_8UC1),
    * and return the result image
    * Inputs: source: the source matrix(BGR)
    * Variables:
    *  rows: number of rows of the source matrix
    *  cols: number of cols of the source matrix
    *  grayscale_image: The grayscale image that you will obtain and return
    */
    int rows = source.rows;
    int cols = source.cols;
    Mat grayscale_image(rows, cols, CV_8UC1);

    // convert BGR to grayscale using the formula
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            Vec3b bgrPixel = source.at<Vec3b>(i, j);
            uchar grayValue = (uchar) (0.2989 * bgrPixel[2] + 0.5870 * bgrPixel[1] + 0.1140 * bgrPixel[0]);
            grayscale_image.at<uchar>(i, j) = grayValue;
        }
    }

    return grayscale_image;

}

Mat grayscale_2_binary(Mat source, int threshold){
    /*
    * Create a function that will convert a grayscale image (CV_8UC1 type) to a binary image (CV_8UC1),
    * and return the result image
    * Inputs:
    *  source: the source matrix(grayscale)
    *  threshold: the value that will be used to create the binary image
    * Variables:
    *  rows: number of rows of the source matrix
    *  cols: number of cols of the source matrix
    *  binary_image: The binary image that you will obtain and return
    */
    int rows, cols;
    Mat binary;

    //*****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    // Get the dimensions of the source image
    rows = source.rows;
    cols = source.cols;

    // Create the binary image with the same dimensions as the source image
    binary = Mat::zeros(rows, cols, CV_8UC1);

    // Loop through each pixel in the source image
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            // If the pixel value is greater than the threshold, set the corresponding pixel in the binary image to 255 (white)
            if(source.at<uchar>(i, j) > threshold){
                binary.at<uchar>(i, j) = 255;
            }else if(source.at<uchar>(i, j) < threshold){
                binary.at<uchar>(i, j) = 0;
            }
        }
    }

    //*****END OF YOUR CODE(DO NOT DELETE / MODIFY THIS LINE) *****

    return binary;
}

image_channels_hsv bgr_2_hsv(image_channels_bgr bgr_channels) {
    /*
    * Create a function that will convert a BGR image represented as separate color channels
    * to an HSV image also represented as separate color channels, and return the result
    * Inputs: bgr_channels: the input image represented as BGR channels
    * Variables:
    *  rows: number of rows of the input image
    *  cols: number of cols of the input image
    *  hsv_channels: the output image represented as HSV channels
    */
    int rows = bgr_channels.B.rows;
    int cols = bgr_channels.B.cols;
    Mat H(rows, cols, CV_8UC1);
    Mat S(rows, cols, CV_8UC1);
    Mat V(rows, cols, CV_8UC1);
    image_channels_hsv hsv_channels;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            double r = bgr_channels.R.at<uchar>(i, j) / 255.0;
            double g = bgr_channels.G.at<uchar>(i, j) / 255.0;
            double b = bgr_channels.B.at<uchar>(i, j) / 255.0;
            double c_max = max({r, g, b});
            double c_min = min({r, g, b});
            double delta = c_max - c_min;
            double H_val, S_val, V_val;
            if (delta == 0) {
                H_val = 0;
            } else if (c_max == r) {
                H_val = 60.0 * fmod(((g - b) / delta), 6.0);
            } else if (c_max == g) {
                H_val = 60.0 * (((b - r) / delta) + 2.0);
            } else {
                H_val = 60.0 * (((r - g) / delta) + 4.0);
            }
            if (c_max == 0) {
                S_val = 0;
            } else {
                S_val = (delta / c_max) * 255.0;
            }
            V_val = c_max * 255.0;
            H.at<uchar>(i, j) = static_cast<uchar>(H_val / 2);
            S.at<uchar>(i, j) = static_cast<uchar>(S_val);
            V.at<uchar>(i, j) = static_cast<uchar>(V_val);
        }
    }

    hsv_channels.H = H;
    hsv_channels.S = S;
    hsv_channels.V = V;

    return hsv_channels;
}
void display_hsv_channels(image_channels_hsv hsv_channels){

    /*
    * Display the three channels
    * Inputs:
    *    hsv_channels: structure that stores the H, S, V channels of an image.
    *      In order to display them don't forget to normalize them accordingly
    *  Variables:
    *    rows: number of rows of the source matrix
    *    cols: number of cols of the source matrix
    *    H_norm, S_norm, V_norm: Normalized matrices.
    */

    int rows, cols;
    Mat H_norm, S_norm, V_norm;

    // Normalize each channel
    normalize(hsv_channels.H, H_norm, 0, 255, NORM_MINMAX, CV_8UC1);
    normalize(hsv_channels.S, S_norm, 0, 255, NORM_MINMAX, CV_8UC1);
    normalize(hsv_channels.V, V_norm, 0, 255, NORM_MINMAX, CV_8UC1);

    // Display each channel in a different window
    namedWindow("H Channel", WINDOW_NORMAL);
    imshow("H Channel", H_norm);

    namedWindow("S Channel", WINDOW_NORMAL);
    imshow("S Channel", S_norm);

    namedWindow("V Channel", WINDOW_NORMAL);
    imshow("V Channel", V_norm);

    // Wait for a key press
    waitKey(0);
}
bool IsInside(Mat img, int i, int j){
    /*
    * Implement a function called isInside(img, i, j) which checks if the position indicated by
    * the pair (i,j) (row, column) is inside the image img.
    */

    //*****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
    // Check if i and j are within the bounds of the matrix
    if (i >= 0 && i < img.rows && j >= 0 && j < img.cols){
        return true;
    }
    else{
        return false;
    }
    //*****END OF YOUR CODE(DO NOT DELETE / MODIFY THIS LINE) *****

}


int main() {
    Mat image = imread("/Users/tonynecula/Downloads/PI-L2/kids.bmp",
                       IMREAD_COLOR);

    imshow("Original image", image);

    image_channels_bgr bgr_channels = break_channels(image);
    display_channels(bgr_channels);

    Mat greyscale_image = bgr_2_grayscale(image);
    imshow("Grayscale image", greyscale_image);

    //Try with 30, 60, 180, 220
    Mat binary_image = grayscale_2_binary(greyscale_image, 127);
    imshow("Binary image", binary_image);

    image_channels_hsv hsv_channels = bgr_2_hsv(bgr_channels);
    display_hsv_channels(hsv_channels);

    bool is_inside = IsInside(greyscale_image, 30, 50);
    cout << is_inside;

    waitKey(0);
    return 0;
}