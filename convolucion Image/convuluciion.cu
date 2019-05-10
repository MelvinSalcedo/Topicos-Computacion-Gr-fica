#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>
#include <cstdlib>
#include <time.h>
#include "CImg.h"

using namespace std;
using namespace cimg_library;

#include <iostream>
#define BLOCK_SIZE 32
#define WA 512   
#define HA 512     
#define HC 3     
#define WC 3
#define WB (WA - WC + 1)
#define HB (HA - HC + 1)

using namespace std;
__global__ void Convolucion(float* A, float* B, float* C, int numARows, int numACols, int numBRows, int numBCols, int numCRows, int numCCols)
{
	int col = blockIdx.x * (BLOCK_SIZE - WC + 1) + threadIdx.x;
	int row = blockIdx.y * (BLOCK_SIZE - WC + 1) + threadIdx.y;
	int row_i = row - WC + 1;
	int col_i = col - WC + 1;

	float tmp = 0;

	__shared__ float shm[BLOCK_SIZE][BLOCK_SIZE];

	if (row_i < WA && row_i >= 0 && col_i < WA && col_i >= 0)
	{
		shm[threadIdx.y][threadIdx.x] = A[col_i * WA + row_i];
	}
	else
	{
		shm[threadIdx.y][threadIdx.x] = 0;
	}

	__syncthreads();

	if (threadIdx.y < (BLOCK_SIZE - WC + 1) && threadIdx.x < (BLOCK_SIZE - WC + 1) && row < (WB - WC + 1) && col < (WB - WC + 1))
	{
		for (int i = 0; i< WC;i++)
			for (int j = 0;j<WC;j++)
				tmp += shm[threadIdx.y + i][threadIdx.x + j] * C[j*WC + i];
		B[col*WB + row] = tmp;
	}
}


int main(int argc, char** argv)
{
	CImg<unsigned char> src("a.png");
    int width = src.width();
    int height = src.height();
    
    unsigned long size = src.size();
    
    int A[width][width];
    
	cudaError_t error;
	cudaEvent_t start_G, stop_G;

	cudaEventCreate(&start_G);
	cudaEventCreate(&stop_G);

	unsigned int size_A = WA * HA;
	unsigned int mem_size_A = sizeof(float) * size_A;
	float* h_A = (float*)malloc(mem_size_A);

	unsigned int size_B = WB * HB;
	unsigned int mem_size_B = sizeof(float) * size_B;
	float* h_B = (float*)malloc(mem_size_B);

	unsigned int size_C = WC * HC;
	unsigned int mem_size_C = sizeof(float) * size_C;
	float* h_C = (float*)malloc(mem_size_C);

	//Sobel derivada en x
	/*h_C[0]=-1;h_C[1]=0;h_C[2]=1;
	h_C[3]=-2;h_C[4]=0;h_C[5]=2;
	h_C[6]=-1;h_C[7]=0;h_C[8]=1;*/
	
	//Sobel derivada en y
	/*h_C[0]=-1;h_C[1]=-2;h_C[2]=-1;
	h_C[3]=0;h_C[4]=0;h_C[5]=0;
	h_C[6]=1;h_C[7]=2;h_C[8]=1;*/
	
	//filtro de prewit derivada en x
	/*h_C[0]=-1;h_C[1]=0;h_C[2]=1;
	h_C[3]=-1;h_C[4]=0;h_C[5]=1;
	h_C[6]=-1;h_C[7]=0;h_C[8]=1;*/
	
	//filtro de scharr derivada en x
	/*h_C[0]=-3;h_C[1]=0;h_C[2]=3;
	h_C[3]=-10;h_C[4]=0;h_C[5]=10;
	h_C[6]=-1;h_C[7]=0;h_C[8]=1;*/
	
	//filtro de laplace
	h_C[0]=-1;h_C[1]=-1;h_C[2]=-1;
	h_C[3]=-1;h_C[4]=8;h_C[5]=-1;
	h_C[6]=-1;h_C[7]=-1;h_C[8]=-1;
	

	//int B[xF][yF]={{0,0,0},{0,1,0},{0,0,0}};
	int n=0;
	for (int x=0;x<width;x++){
		for (int y=0;y<width;y++){
			unsigned char r =(float)src(x,y,0,0);
			unsigned char g =(float)src(x,y,0,1);
			unsigned char b =(float)src(x,y,0,2);
									
			int _gray = (unsigned int)((float)(r + g + b) / 3.0f + 0.5);
			
			src(x,y,0,0)=_gray;
			src(x,y,0,1)=_gray;
			src(x,y,0,2)=_gray;
			
			A[x][y] =_gray;
			h_A[n]=_gray;
			//cout<<_gray<<" ";
			n++;
		}	
		//cout<<endl;
	}
	
	src.display();// imagen transformada en esacala de grises
	float* d_A;
	float* d_B;
	float* d_C;

	cudaMalloc((void**)&d_A, mem_size_A);
	cudaMalloc((void**)&d_B, mem_size_B);
	cudaMalloc((void**)&d_C, mem_size_C);

	cudaMemcpy(d_A, h_A, mem_size_A, cudaMemcpyHostToDevice);
	cudaMemcpy(d_C, h_C, mem_size_C, cudaMemcpyHostToDevice);

	dim3 threads(BLOCK_SIZE, BLOCK_SIZE);
	dim3 grid((WB - 1) / (BLOCK_SIZE - WC + 1), (WB - 1) / (BLOCK_SIZE - WC + 1));

	Convolucion << < grid, threads >> >(d_A, d_B, d_C, HA, WA, HB, WB, HC, WC);
	
	cudaMemcpy(h_B, d_B, mem_size_B, cudaMemcpyDeviceToHost);

	for (int i = 0;i < HB;i++)
	{
		for (int j = 0;j < WB;j++)
		{
			src(i,j,0,0)=h_B[i*HB + j];
			src(i,j,0,1)=h_B[i*HB + j];
			src(i,j,0,2)=h_B[i*HB + j];
			
			//cout<<h_B[i*HB + j]<<" ";
		}
	}
	

	free(h_A);
	free(h_B);
	free(h_C);
	cudaFree(d_A);
	cudaFree(d_B);
	cudaFree(d_C);
	src.display();
	return EXIT_SUCCESS;
}
