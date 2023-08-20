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

    // make a negative version of the image
    Mat img3(img.rows, img.cols, CV_8UC3, Scalar(0, 0, 0));
    for (int i = 0; i < img.rows; i++) {
        for (int j = 0; j < img.cols; j++) {
            img3.at<Vec3b>(i, j)[0] = 255 - img.at<Vec3b>(i, j)[0];
            img3.at<Vec3b>(i, j)[1] = 255 - img.at<Vec3b>(i, j)[1];
            img3.at<Vec3b>(i, j)[2] = 255 - img.at<Vec3b>(i, j)[2];
        }
    }

    //make a mirrored version of the image horizotally
    Mat img4(img.rows, img.cols, CV_8UC3, Scalar(0, 0, 0));
    for (int i = 0; i < img.rows; i++) {
        for (int j = 0; j < img.cols; j++) {
            img4.at<Vec3b>(i, j)[0] = img.at<Vec3b>(i, img.cols - j - 1)[0];
            img4.at<Vec3b>(i, j)[1] = img.at<Vec3b>(i, img.cols - j - 1)[1];
            img4.at<Vec3b>(i, j)[2] = img.at<Vec3b>(i, img.cols - j - 1)[2];
        }
    }

    //make a mirrored version of the image vertically
    Mat img5(img.rows, img.cols, CV_8UC3, Scalar(0, 0, 0));
    for (int i = 0; i < img.rows; i++) {
        for (int j = 0; j < img.cols; j++) {
            img5.at<Vec3b>(i, j)[0] = img.at<Vec3b>(img.rows - i - 1, j)[0];
            img5.at<Vec3b>(i, j)[1] = img.at<Vec3b>(img.rows - i - 1, j)[1];
            img5.at<Vec3b>(i, j)[2] = img.at<Vec3b>(img.rows - i - 1, j)[2];
        }
    }

    //rotate the image 90 degrees clockwise
    Mat img6(img.cols, img.rows, CV_8UC3, Scalar(0, 0, 0));
    for (int i = 0; i < img.rows; i++) {
        for (int j = 0; j < img.cols; j++) {
            img6.at<Vec3b>(j, img.rows - i - 1)[0] = img.at<Vec3b>(i, j)[0];
            img6.at<Vec3b>(j, img.rows - i - 1)[1] = img.at<Vec3b>(i, j)[1];
            img6.at<Vec3b>(j, img.rows - i - 1)[2] = img.at<Vec3b>(i, j)[2];
        }
    }

    //increase the brightness of the image
    Mat img7(img.rows, img.cols, CV_8UC3, Scalar(0, 0, 0));
    for (int i = 0; i < img.rows; i++) {
        for (int j = 0; j < img.cols; j++) {
            img7.at<Vec3b>(i, j)[0] = saturate_cast<uchar>(img.at<Vec3b>(i, j)[0] + 50);
            img7.at<Vec3b>(i, j)[1] = saturate_cast<uchar>(img.at<Vec3b>(i, j)[1] + 50);
            img7.at<Vec3b>(i, j)[2] = saturate_cast<uchar>(img.at<Vec3b>(i, j)[2] + 50);
        }
    }

    //decrease the brightness of the image
    Mat img8(img.rows, img.cols, CV_8UC3, Scalar(0, 0, 0));
    for (int i = 0; i < img.rows; i++) {
        for (int j = 0; j < img.cols; j++) {
            img8.at<Vec3b>(i, j)[0] = saturate_cast<uchar>(img.at<Vec3b>(i, j)[0] - 50);
            img8.at<Vec3b>(i, j)[1] = saturate_cast<uchar>(img.at<Vec3b>(i, j)[1] - 50);
            img8.at<Vec3b>(i, j)[2] = saturate_cast<uchar>(img.at<Vec3b>(i, j)[2] - 50);
        }
    }

 
    imwrite(argv[2],img3);
    imwrite(argv[3],img4);
    imwrite(argv[4],img5);
    imwrite(argv[5],img6);
    imwrite(argv[6],img7);
    imwrite(argv[7],img8);
    
    
    // Wait for any keystroke
    waitKey(0);
    return 0;
}