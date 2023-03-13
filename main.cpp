#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

bool IsInside(Mat img, int i, int j){
    /*
    * Implement a function called isInside(img, i, j) which checks if the position indicated by
    * the pair (i,j) (row, column) is inside the image img.
    */

    //*****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    //*****END OF YOUR CODE(DO NOT DELETE / MODIFY THIS LINE) *****

}

typedef struct grayscale_mapping{
    uchar* grayscale_values; //hold the grayscale values after thresholding
    uchar count_grayscale_values; //hold the number grayscale values after thresholding
};

int* compute_histogram(Mat source, int histogram_bins){

    /*
    * Compute  the  histogram  for  a  given  grayscale  image (in  an  array  of  integers  having dimension 256)
    */

    int rows;
    int cols;
    int* histogram;

    //*****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    //*****END OF YOUR CODE(DO NOT DELETE / MODIFY THIS LINE) *****

    return histogram;

}

int* compute_histogram_custom(Mat source, int histogram_bins){

    /*
     * Compute the histogram for a given number of bins m≤ 256.
     */

    int rows;
    int cols;
    int* histogram;

    //*****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    //*****END OF YOUR CODE(DO NOT DELETE / MODIFY THIS LINE) *****

    return histogram;

}

float* compute_pdf(int* histogram, Mat source){
    /*
     *Compute the PDF (in an array of floats of dimension 256)
     */

    int rows;
    int cols;
    int no_grayscale_values;
    float* pdf;

    //*****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    //*****END OF YOUR CODE(DO NOT DELETE / MODIFY THIS LINE) *****

    return pdf;

}

void showHistogram(const string& name, int* hist, const int  hist_cols, const int hist_height){
    /*
     * Hint: Look in the lab work
     */

    //*****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    //*****END OF YOUR CODE(DO NOT DELETE / MODIFY THIS LINE) *****

}

grayscale_mapping multi_level_thresholding(Mat source, int wh, float th, float* pdf){
    /*
     * Implement the multilevel thresholding algorithm from section 3.3.
     */

    grayscale_mapping map;

    //*****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    //*****END OF YOUR CODE(DO NOT DELETE / MODIFY THIS LINE) *****

    return map;

}

uchar find_closest_histogram_maximum(uchar old_pixel, grayscale_mapping gray_map){

    /*
     * Find the corresponding quantized value to map a pixel
     * Hint: Look in the gray_map and find out the value that resides at index argmin of the distance between old_pixel
     *      and the values in gray_map
     */

    uchar new_grayscale_value;

    //*****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    //*****END OF YOUR CODE(DO NOT DELETE / MODIFY THIS LINE) *****


    return new_grayscale_value;
}

Mat draw_multi_thresholding(Mat source, grayscale_mapping grayscale_map){

    /*
     * Draw the new multi level threshold image by mapping each pixel to the corresponding quantized values
     * Hint: Look in the grayscale_map structure for all the obtained grayscale values and for each pixel in the
     *      source image assign the correct value. You may use the find_closest_histogram_maximum function
     */

    Mat result;

    //*****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    //*****END OF YOUR CODE(DO NOT DELETE / MODIFY THIS LINE) *****


    return result;
}

uchar update_pixel_floyd_steinberg_dithering(uchar pixel_value, int value){
    /*
     * Update the value of a pixel in the floyd_steinberg alg.
     * Take care of the values bellow 0 or above 255. Clamp them.
     */

    //*****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    //*****END OF YOUR CODE(DO NOT DELETE / MODIFY THIS LINE) *****

}

Mat floyd_steinberg_dithering(Mat source, grayscale_mapping grayscale_map){

    /*
     * Enhance  the  multilevel  thresholding  algorithm  using  the  Floyd-Steinberg  dithering from section 3.4.
     * Hint: Use the update_pixel_floyd_steinberg_dithering when spreading the error
     */

    Mat result;

    //*****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    //*****END OF YOUR CODE(DO NOT DELETE / MODIFY THIS LINE) *****

    return result;
}

int main() {
    Mat cameraman = imread("YOUR_PATH/cameraman.bmp",
                           IMREAD_GRAYSCALE);
    Mat saturn = imread("YOUR_PATH/saturn.bmp",
                        IMREAD_GRAYSCALE);

    imshow("Cameraman original", cameraman);
    imshow("Saturn original", saturn);

    int* histogram_cameraman = compute_histogram(cameraman, 256);
    float* pdf_cameraman = compute_pdf(histogram_cameraman, cameraman);

    int* histogram_saturn = compute_histogram(saturn, 256);
    float* pdf_saturn = compute_pdf(histogram_saturn, saturn);

    printf("Some histogram values are: ");
    for(int i=50; i < 56; i++){
        printf("%d ", histogram_cameraman[i]);
    }
    printf("\n");

    printf("Some pdf values are: ");
    for(int i=50; i < 56; i++){
        printf("%f ", pdf_cameraman[i]);
    }

    showHistogram("Histogram", histogram_cameraman, 256, 100);

    int* histogram_custom = compute_histogram_custom(cameraman, 40);
    showHistogram("Histogram reduced bins", histogram_custom, 40, 100);

    grayscale_mapping grayscale_map_saturn = multi_level_thresholding(saturn, 5, 0.0003, pdf_saturn);
    grayscale_mapping grayscale_map_cameraman = multi_level_thresholding(saturn, 5, 0.0003, pdf_cameraman);

    Mat image_multi_threshold_cameraman = draw_multi_thresholding(cameraman, grayscale_map_cameraman);
    imshow("Multi level threshold cameraman", image_multi_threshold_cameraman);

    Mat fsd_cameraman = floyd_steinberg_dithering(cameraman, grayscale_map_cameraman);
    imshow("Floyd Steinberg Dithering cameraman", fsd_cameraman);

    Mat image_multi_threshold_saturn = draw_multi_thresholding(saturn, grayscale_map_saturn);
    imshow("Multi level threshold saturn", image_multi_threshold_saturn);

    Mat fsd_saturn = floyd_steinberg_dithering(saturn, grayscale_map_saturn);
    imshow("Floyd Steinberg Dithering saturn", fsd_saturn);

    waitKey(0);
    return 0;
}