#include <iostream>
#include <vector>
#include <stdio.h>
#include <fstream>
#include <string.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>    
#include "FormatBMP.h"
using namespace std;

int main(int argc, char *argv[]){
    cv::Mat image= cv::imread("Shapes_24.bmp");   
    // create image window named "My Image"
    cv::namedWindow("My Image");
    // show the image on window
    cv::imshow("My Image", image);
    // wait key for 5000 ms
    cv::waitKey(5000);

    bmpFileHeader fileHead;
    bmpInfoHeader infoHead;
    unsigned char *img;
    unsigned char *img_edit;
    img = readBMP(argv[1], &fileHead, &infoHead);
    DisplayInfo(&infoHead);
    img_edit = sumarg(infoHead, img, 50);
    // saveImg("test_img2.bmp", infoHead, fileHead, img);
    saveImg("editada.bmp", infoHead, fileHead, img_edit);
    // printf("DATA %d", img);
    // std::cout << "DATA" << img << '\n';

    cv::Mat image2= cv::imread("editada.bmp");   
    // create image window named "My Image"
    cv::namedWindow("My Image");
    // show the image on window
    cv::imshow("My Image", image2);
    // wait key for 5000 ms
    cv::waitKey(5000);

    return 0;
    
    // read an image
   

}
