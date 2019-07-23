#include <iostream>
#include <string>
#include "pch.h"
#include <vector>
#include <cmath>
#include <opencv2\opencv.hpp>

using namespace std;
struct position {
	int x;
	int y;
};
vector<pair<int, int> > PM;

void Template_matching(const string& img_name, const string& template_img_name);
int SSD(cv::Mat& img, cv::Mat& template_img, const int* x, const int* y,float&);
void Indicate_Predicted_Position(cv::Mat& img, cv::Mat& template_img, const position& p);

int main() {

	Template_matching("input/boards.jpg", "input/a1.jpg");

	return 0;
}

void Template_matching(const std::string& img_name, const std::string& template_img_name) {

	cv::Mat img = cv::imread(img_name);
	cv::Mat template_img = cv::imread(template_img_name);


	int min = 40000000;
	int r = 0;
	struct position p = { 0,0 };
	float normalisar = 0;

	std::cout << "SSD" << std::endl;
	for (int y = 0; y <= img.rows - template_img.rows; ++y) {
		for (int x = 0; x <= img.cols - template_img.cols; ++x) {
			r = SSD(img, template_img, &x, &y,normalisar);
			//cout << normalisar << endl;
			if (normalisar > 0.5) {
			
			}
			if (min > r) {
				cout << "punto registrado " <<r<<endl;
				min = r;
				p.x = x;
				p.y = y;
				PM.push_back(make_pair(x,y));
			}
		}
	}

	std::cout << "Indicate" << std::endl;
	cv::Mat copy_img;
	img.convertTo(copy_img, CV_8U);
	Indicate_Predicted_Position(copy_img, template_img, p);

	cv::imshow("img", img);
	cv::imshow("template_img", template_img);
	cv::imshow("matchimg_result", copy_img);
	cv::waitKey();
}

int SSD(cv::Mat& img, cv::Mat& template_img, const int* x, const int* y,float &normalisar) {
	int r = 0;
	int temp = 0;

	int i = 0;
	int j = 0;
	int c = 0;


	int T=0, I = 0;
	float SQRT_ = 0;
	int a2 = 0, b2 = 0,c2=0;

	for (i = 0; i < template_img.rows; ++i) {
		for (j = 0; j < template_img.cols; ++j) {
			for (c = 0; c < img.channels(); ++c) {
				
				T= static_cast<int>(template_img.data[i*template_img.step + j * template_img.elemSize()
					+ c]);
				//cout << T;
				I = static_cast<int>(img.data[(i + *y)*img.step + (j + *x)*img.elemSize() + c]);

				temp = T - I;
				
				r += temp * temp;

				//a2 += T*T;
				//b2 += I*I;


				

			}
			cout <<endl;
		}
	}
	//SQRT_ = sqrt(a2*b2);
	//normalisar = r/SQRT_;
	//cout << SQRT_ <<"   "<<r<< endl;
	return r;
}

void Indicate_Predicted_Position(cv::Mat& img, cv::Mat& template_img, const position& p) {
	int y = 0;
	int x = 0;
	cout << PM.size()<<endl;
	for (int i = 0; i < PM.size(); i++) {
		for (y = 0; y < img.rows; ++y) {
			for (x = 0; x < img.cols; ++x) {

				if (y == PM[i].second || y == (PM[i].second + template_img.rows)) {
					if (x > PM[i].first && x < PM[i].first + template_img.cols) {
						img.data[y*img.step + x * img.elemSize() + 0] = static_cast<uchar>(255);
						img.data[y*img.step + x * img.elemSize() + 1] = static_cast<uchar>(0);
						img.data[y*img.step + x * img.elemSize() + 2] = static_cast<uchar>(0);
					}
				}

				if (x == PM[i].first || x == (PM[i].first + template_img.cols)) {
					if (y > PM[i].second && y < PM[i].second + template_img.rows) {
						img.data[y*img.step + x * img.elemSize() + 0] = static_cast<uchar>(0);
						img.data[y*img.step + x * img.elemSize() + 1] = static_cast<uchar>(0);
						img.data[y*img.step + x * img.elemSize() + 2] = static_cast<uchar>(255);
					}
				}
			}
		}
	}
}