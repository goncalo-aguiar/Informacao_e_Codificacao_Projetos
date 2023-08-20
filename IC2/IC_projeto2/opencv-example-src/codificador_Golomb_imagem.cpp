#include "Golomb.cpp"

#include <iostream>
#include <vector>
#include <cmath>
#include <fftw3.h>
#include <sndfile.hh>
#include "BitStream.cpp"

#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

constexpr size_t FRAMES_BUFFER_SIZE = 65536;

int max(int num1, int num2)
{   
    if(num1 > num2){
        return  num1;
    } else {
        return num2;
    }
}

int min(int num1, int num2) 
{
    if(num1 > num2){
        return num2;
    } else {
        return num1;
    }
}

int main(int argc, char *argv[]) {
    int m = stoi(argv[2]);
    bool verbose { false };

    fstream my_file;
	my_file.open("ficheiro_codificado_imagem", ios::out);
	my_file.close();
    Golomb golomb{};
	BitStream bitstream{"ficheiro_codificado_imagem","w"};

	Mat img = imread(argv[1]);
   
    // Error Handling
    if (img.empty()) {
        cout << "Image File "<< "Not Found" << endl;
  
        // wait for any key press
        cin.get();
        return -1;
    }
    
    
    // HEADER
    cout << "Encoding Header" << endl;
    string header = golomb.encodeInt(img.rows,m);
    header = header + golomb.encodeInt(img.cols,m);

    bitstream.writeNBits(header);
    cout<< "Ended encoding Header..."<< endl;
    //----------------
    cout << "Starting encoding image..." << endl;
    int a,b,c,x;
    int calculatedR, calculatedG, calculatedB;
    string codifiedR,codifiedG,codifiedB;
    
    
    // percorre a imagem
    for (int i = 0; i < img.rows; i++) {
        for (int j = 0; j < img.cols; j++) {

            if(i==0 || j==0){
                calculatedR = 0;
                calculatedG = 0;
                calculatedB = 0;

            } else {
                
                // calcula perdictors para as diferentes cores
                // RED
                a = img.at<Vec3b>(i, j-1)[0];
                b = img.at<Vec3b>(i-1, j)[0];
                c = img.at<Vec3b>(i-1, j-1)[0];

                if (c >= max(a, b))
                    x = min(a, b);
                else if (c < min(a, b))
                    x = max(a, b);
                else
                    x = a + b - c;

                calculatedR = x;
                
                // GREEN
                a = img.at<Vec3b>(i, j-1)[1];
                b = img.at<Vec3b>(i-1, j)[1];
                c = img.at<Vec3b>(i-1, j-1)[1];

                if (c >= max(a, b))
                    x = min(a, b);
                else if (c < min(a, b))
                    x = max(a, b);
                else
                    x = a + b - c;

                calculatedG = x;

                // BLUE
                a = img.at<Vec3b>(i, j-1)[2];
                b = img.at<Vec3b>(i-1, j)[2];
                c = img.at<Vec3b>(i-1, j-1)[2];

                if (c >= max(a, b))
                    x = min(a, b);
                else if (c < min(a, b))
                    x = max(a, b);
                else
                    x = a + b - c;

                calculatedB = x;

            }

            int actualR = img.at<Vec3b>(i, j)[0]; 
            int actualG = img.at<Vec3b>(i, j)[1]; 
            int actualB = img.at<Vec3b>(i, j)[2]; 


            
            string codified = golomb.encodeInt(actualR - calculatedR,m);
            codified = codified + golomb.encodeInt(actualG - calculatedG,m);
            codified = codified + golomb.encodeInt(actualB - calculatedB,m);

            bitstream.writeNBits(codified); 
            
        }
    }
    cout << "Ended encoding image" << endl;
}


