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

    //*****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    //*****END OF YOUR CODE(DO NOT DELETE / MODIFY THIS LINE) *****

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
    //*****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    //*****END OF YOUR CODE(DO NOT DELETE / MODIFY THIS LINE) *****

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
    int rows, cols;
    Mat grayscale_image;

    //*****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    //*****END OF YOUR CODE(DO NOT DELETE / MODIFY THIS LINE) *****

    return grayscale_image;

}

Mat grayscale_2_binary(Mat source, int threshold){
    /*
    * Create a function for converting from grayscale to black and white (binary), using (2.2).
    * Test the operation on multiple images, and using multiple thresholds.
    * Inputs:
    *    source: grayscale image
    *    threshold: the threshold you are going to use to perform the binarization
    *  Variables:
    *    rows: number of rows of the source matrix
    *    cols: number of cols of the source matrix
    *    binary: the resulted binarized image
    */

    int rows, cols;
    Mat binary;

    //*****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    //*****END OF YOUR CODE(DO NOT DELETE / MODIFY THIS LINE) *****

    return binary;
}

image_channels_hsv bgr_2_hsv(image_channels_bgr bgr_channels){
    /*
    * Create a function that will compute the H, S and V values from the R, G, B channels of
    * an image, using the equations from 2.6. Store each value (H, S, V) in a CV_8UC1 matrix that will be
    * stored in an image_channels_hsv struct.
    * Inputs:
    *    bgr_channels: structure that stores the B, G, R channels of an image
    * Variables:
    *    rows: number of rows of the source matrix
    *    cols: number of cols of the source matrix
    *    H, S, V: matrices that will store the values of the 3 different channels (Pay attention to the type of elements
    *       that are stored in these matrices.
    *    hsv_channels: structure that will store the H, S, V channels
    */

    int rows, cols;
    Mat H, S, V;
    image_channels_hsv hsv_channels;

    //*****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    //*****END OF YOUR CODE(DO NOT DELETE / MODIFY THIS LINE) *****

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

    //*****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    //*****END OF YOUR CODE(DO NOT DELETE / MODIFY THIS LINE) *****

}

bool IsInside(Mat img, int i, int j){
    /*
    * Implement a function called isInside(img, i, j) which checks if the position indicated by
    * the pair (i,j) (row, column) is inside the image img.
    */

    //*****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    //*****END OF YOUR CODE(DO NOT DELETE / MODIFY THIS LINE) *****

}


int main() {
    Mat image = imread("YOUR_PATH_HERE",
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
