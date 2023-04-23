#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int n8_di[8] = {0,-1,-1, -1, 0, 1, 1, 1};
int n8_dj[8] = {1, 1, 0, -1, -1,-1, 0, 1};

Point find_P_0(Mat source){
    /*
     * Find the initial point of the contour and return it
     */
    Point P_0;

    // Start from the top left corner of the image and look for the first object pixel
    for(int i = 0; i < source.rows; i++){
        for(int j = 0; j < source.cols; j++){
            if(source.at<uchar>(i,j) == 0){
                P_0 = Point(j,i);
                return P_0;
            }
        }
    }

    return P_0;
}

typedef struct contour{
    vector<Point> border;
    vector<int> dir_vector;
};

contour extract_contour(Mat source, Point P_0){

    /*
     * Use the border tracing algorithm in order to extract the contour
     * Save it as a vector of points and a vector of directions
     */

    int dir;
    Point P_current;
    std::vector<Point> border;
    std::vector<int> dir_vector;

    P_current = P_0;
    dir = 0;

    do{
        border.push_back(P_current);
        dir_vector.push_back(dir);

        int dir_start;
        if(dir%2==0){
            dir_start = (dir+7)%8;
        }
        else{
            dir_start = (dir+6)%8;
        }

        bool found = false;
        for(int i = 0; i < 8; i++){
            int k = (dir_start+i)%8;
            Point P_check = P_current + Point(n8_dj[k], n8_di[k]);
            if(source.at<uchar>(P_check) == 0){
                P_current = P_check;
                dir = k;
                found = true;
                break;
            }
        }
        if(!found){
            break;
        }
    }while(P_current != P_0 || border.size() == 0);

    return {border, dir_vector};
}

Mat draw_contour(contour cnt, Mat source){

    /*
     * Draw the contour using the border variable from cnt structure
     */

    Mat dst;
    cvtColor(source, dst, COLOR_GRAY2BGR);

    for(int i = 0; i < cnt.border.size()-1; i++){
        line(dst, cnt.border[i], cnt.border[i+1], Scalar(0,0,255), 2);
    }
    line(dst, cnt.border[cnt.border.size()-1], cnt.border[0], Scalar(0,0,255), 2);

    return dst;
}

void print_AC_DC_chain_codes(contour cnt) {
    /*
     * Print the AC and DC chain codes
     * Hint: You have to compute the DC one
     */

    printf("The AC vector is: ");

    //*****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    for (size_t i = 0; i < cnt.dir_vector.size(); i++) {
        printf("%d ", cnt.dir_vector[i]);
    }

    //*****END OF YOUR CODE(DO NOT DELETE / MODIFY THIS LINE) *****

    printf("\nThe DC vector is: ");

    //*****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    vector<int> dc_chain_codes;
    for (size_t i = 1; i < cnt.dir_vector.size(); i++) {
        int dc = (cnt.dir_vector[i] - cnt.dir_vector[i - 1] + 8) % 8;
        dc_chain_codes.push_back(dc);
    }

    for (size_t i = 0; i < dc_chain_codes.size(); i++) {
        printf("%d ", dc_chain_codes[i]);
    }

    //*****END OF YOUR CODE(DO NOT DELETE / MODIFY THIS LINE) *****
}

Mat contour_reconstruction(FILE *pf, Mat background) {

    // Read the starting point
    int startX, startY;
    fscanf(pf, "%d %d", &startX, &startY);

    // Read the AC chain codes
    std::vector<int> ac_chain_codes;
    int code;
    while (fscanf(pf, "%d", &code) != EOF) {
        ac_chain_codes.push_back(code);
    }

    // Reconstruct the contour using the AC chain codes
    Point current_point(startX, startY);
    background.at<uchar>(current_point) = 0; // Set the initial pixel value

    for (const int &ac : ac_chain_codes) {
        current_point.x += n8_dj[ac];
        current_point.y += n8_di[ac];
        background.at<uchar>(current_point) = 0;
    }

    return background;
}



int main() {
    Mat source = imread("/Users/tonynecula/Downloads/PI-L6/star.bmp",
                        IMREAD_GRAYSCALE);

    imshow("Original Image", source);

    Point P_0 = find_P_0(source);
    contour cnt = extract_contour(source, P_0);
    cout << "Border size: " << cnt.border.size() << endl;
    cout << "Direction vector size: " << cnt.dir_vector.size() << endl;
    Mat mat_cnt = draw_contour(cnt, source);

    imshow("Contour", mat_cnt);

    print_AC_DC_chain_codes(cnt);

    FILE *pf;
    pf = fopen("/Users/tonynecula/Downloads/PI-L6/reconstruct.txt", "r");
    Mat background = imread("/Users/tonynecula/Downloads/PI-L6/gray_background.bmp", IMREAD_GRAYSCALE);

    Mat reconstruction = contour_reconstruction(pf, background);

    imshow("Reconstruction", reconstruction);

    waitKey();

    return 0;
}