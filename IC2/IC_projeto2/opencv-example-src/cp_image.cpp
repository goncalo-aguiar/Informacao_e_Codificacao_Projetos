#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
  
// Driver code
int main(int argc, char** argv)
{
    
    Mat img = imread(argv[1]);
   
    // Error Handling
    if (img.empty()) {
        cout << "Image File "<< "Not Found" << endl;
  
        // wait for any key press
        cin.get();
        return -1;
    }

    //make a copy of the image
    Mat img2(img.rows, img.cols, CV_8UC3, Scalar(0, 0, 0));
    for (int i = 0; i < img.rows; i++) {
        for (int j = 0; j < img.cols; j++) {
            img2.at<Vec3b>(i, j)[0] = img.at<Vec3b>(i, j)[0];
            img2.at<Vec3b>(i, j)[1] = img.at<Vec3b>(i, j)[1];
            img2.at<Vec3b>(i, j)[2] = img.at<Vec3b>(i, j)[2];
        }
    }

    imwrite(argv[2],img2);
       
    
    // Wait for any keystroke
    waitKey(0);
    return 0;
}