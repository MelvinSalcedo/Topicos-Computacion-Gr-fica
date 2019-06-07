#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

float Zoom=10.0;



void InterpolacionVecinosCercanos(){
	Mat ImagenEntrada = imread("lena.jpg");
	int h = ImagenEntrada.rows*Zoom;
	int w = ImagenEntrada.cols*Zoom;

	Mat ImagenSalida(h,w, CV_8UC3, Scalar(0, 0, 0));

	for(int x = 0; x < h ; x++){
		for (int y = 0; y < w; y++)
		{
			float Rx=x/Zoom;
			float Ry=y/Zoom;

			int F1=int ((x/Zoom)+0.5);
			int F2=int ((y/Zoom)+0.5);

			ImagenSalida.at<Vec3b>(x,y)[0] = ImagenEntrada.at<Vec3b>(F1,F2)[0];
			ImagenSalida.at<Vec3b>(x,y)[1] = ImagenEntrada.at<Vec3b>(F1,F2)[1];
			ImagenSalida.at<Vec3b>(x,y)[2] = ImagenEntrada.at<Vec3b>(F1,F2)[2];
		}
	}
	imshow("Imagen salida",ImagenSalida);
}



void InterpolacionBilineal(){
	Mat ImagenEntrada = imread("lena.jpg");
	
	int h = ImagenEntrada.rows*Zoom;
	int w = ImagenEntrada.cols*Zoom;
	Mat ImagenSalida2(h,w, CV_8UC3, Scalar(0, 0, 0));


	for(int x = 0; x < h ; x++){
		for (int y = 0; y < w; y++)
		{

			float px=x/Zoom;
			float py=y/Zoom;

			if (px >= ImagenEntrada.cols - 1 || py >= ImagenEntrada.rows - 1) break;
			
			int i=(int)px;
			int s=(int)py;

			int d=i+1;
			int r=s+1;

			float a=px-i;
			float b=py-s;

			float R1=(1.0-a)*(1.0-b)*ImagenEntrada.at<Vec3b>(i,s)[0];
			float G1=(1.0-a)*(1.0-b)*ImagenEntrada.at<Vec3b>(i,s)[1];
			float B1=(1.0-a)*(1.0-b)*ImagenEntrada.at<Vec3b>(i,s)[2];

			float R2=a*(1.0-b)*ImagenEntrada.at<Vec3b>(d,s)[0];
			float G2=a*(1.0-b)*ImagenEntrada.at<Vec3b>(d,s)[1];
			float B2=a*(1.0-b)*ImagenEntrada.at<Vec3b>(d,s)[2];
			
			float R3=(1.0-a)*b*ImagenEntrada.at<Vec3b>(i,r)[0];
			float G3=(1.0-a)*b*ImagenEntrada.at<Vec3b>(i,r)[1];
			float B3=(1.0-a)*b*ImagenEntrada.at<Vec3b>(i,r)[2];

			float R4=a*b*ImagenEntrada.at<Vec3b>(d,r)[0];
			float G4=a*b*ImagenEntrada.at<Vec3b>(d,r)[1];
			float B4=a*b*ImagenEntrada.at<Vec3b>(d,r)[2];

			int aa=int(R1+R2+R3+R4);
			int bb=int(G1+G2+G3+G4);
			int cc=int(B1+B2+B3+B4);

			//cout<<(aa+bb+cc)/Zoom<<" | ";

			ImagenSalida2.at<Vec3b>(x,y)[0] = aa;
			ImagenSalida2.at<Vec3b>(x,y)[1] = bb;
			ImagenSalida2.at<Vec3b>(x,y)[2] = cc;

			//cout<<ImagenSalida.at<int>(x,y)<<" ";
			//cout<<" | "<<F1<<" "<<F2<<" ";
		}//cout<<endl;
	}
	imshow("Imagen salida",ImagenSalida2);

}
int main(){
	InterpolacionVecinosCercanos();
	//InterpolacionBilineal();


	//namedWindow( "ImagenEntrada", WINDOW_AUTOSIZE );// Create a window for display.
	
	waitKey(0);
	return 0;
}
