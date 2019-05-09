#include <cuda_runtime.h>
#include "CImg.h"
#include <stdio.h>
#include <cstdlib>
#include <time.h>
#include<iostream>


#define BLOCK_SIZE 32
#define WA 512  
#define HA 512     
#define HC 3     
#define WC 3
#define WB (WA - WC + 1)
#define HB (HA - HC + 1)

using namespace std;
using namespace cimg_library;

// install cimg library
//$ sudo apt install cimg-dev
// compile using nvcc and -lX11 flag
//$ nvcc main.cu -lX11

__global__ void imageFilteringKernel( unsigned char *d_f, int paddedW, int paddedH,int *d_g, int S,unsigned char *d_h,int W,int H )
{

    // Set the padding size and filter size
    unsigned int paddingSize = S;
    unsigned int filterSize = 2 * S + 1;

    // Set the pixel coordinate
    const unsigned int j = blockIdx.x * blockDim.x + threadIdx.x + paddingSize;
    const unsigned int i = blockIdx.y * blockDim.y + threadIdx.y + paddingSize;

    // The multiply-add operation for the pixel coordinate ( j, i )
    if( j >= paddingSize && j < paddedW - paddingSize && i >= paddingSize && i < paddedH - paddingSize ) {
        unsigned int oPixelPos = ( i - paddingSize ) * W + ( j - paddingSize );
        d_h[oPixelPos] = 0.0;
        for( int k = -S; k <= S; k++ ) {
            for( int l = -S; l <= S; l++ ) {
                unsigned int iPixelPos = (( i + k ) * paddedW + ( j + l ));
                unsigned int coefPos = ( k + S ) * filterSize + ( l + S );
                
                d_h[oPixelPos] += d_f[iPixelPos] * d_g[coefPos];
            }
        }
    }

}

__global__ void rgb2gray(unsigned char * d_src, unsigned char * d_dst, int width, int height)
{
    int pos_x = blockIdx.x * blockDim.x + threadIdx.x;
    int pos_y = blockIdx.y * blockDim.y + threadIdx.y;

    if (pos_x >= width || pos_y >= height)
        return;

    /*
     * CImg RGB channels are split, not interleaved.
     * (http://cimg.eu/reference/group__cimg__storage.html)
     */
    unsigned char r = d_src[pos_y * width + pos_x];
    unsigned char g = d_src[(height + pos_y ) * width + pos_x];
    unsigned char b = d_src[(height * 2 + pos_y) * width + pos_x];

    unsigned int _gray = (unsigned int)((float)(r + g + b) / 3.0f + 0.5);
    unsigned char gray = _gray > 255 ? 255 : _gray;

    d_dst[pos_y * width + pos_x] = gray;
}


int main()
{
    //load image
    CImg<unsigned char> src("a.png");
    int width = src.width();
    int height = src.height();
    unsigned long size = src.size();
	cout<<size<<"--------------"<<endl;
    //create pointer to image
    unsigned char *h_src = src.data();
    int *h_filtro;

    CImg<unsigned char> dst(width, height, 1, 1);
    unsigned char *h_dst = dst.data();

    
    
    unsigned int size_C = HC * WC;
	unsigned int mem_size_C = sizeof(float) * size_C;

	unsigned char *d_src;
    unsigned char *d_dst;
    unsigned char *d_dst2;
	int *filtro = (int*)malloc(mem_size_C);
	for(int x=0;x<9;x++){
		filtro[0]=0;
	}

    cudaMalloc((void**)&d_src, size);
    cudaMalloc((void**)&d_dst, width*height*sizeof(unsigned char));
    cudaMalloc((void**)&d_dst2, width*height*sizeof(unsigned char));

    cudaMemcpy(d_src, h_src, size, cudaMemcpyHostToDevice);
    cudaMemcpy(h_filtro, filtro, size_C, cudaMemcpyHostToDevice);



	int hFilterSize = 3 / 2;
    int paddedIWidth = width + 2 * hFilterSize;
    int paddedIHeight = height + 2 * hFilterSize;
    	
	
	
	
    //launch the kernel
    dim3 blkDim (16, 16, 1);
    dim3 grdDim ((width + 15)/16, (height + 15)/16, 1);
    
	/*rgb2gray<<<grdDim, blkDim>>>(d_src, d_dst, width, height);
    //wait until kernel finishes
    cudaDeviceSynchronize();

    //copy back the result to CPU
    cudaMemcpy(h_dst, d_dst, width*height, cudaMemcpyDeviceToHost);*/
    
	
	
	imageFilteringKernel<<<grdDim,blkDim>>>( h_dst, paddedIWidth, paddedIHeight,
						h_filtro, hFilterSize,
						d_dst2, width, height );
						
	cudaDeviceSynchronize();

	
    cudaMemcpy(h_dst, d_dst2, width*height, cudaMemcpyDeviceToHost);
    for (int i = 0; i < 10; ++i){
	cout<<"i = "<<i<<" "<<(h_dst[i]*255)/255.0<<endl;

	}
						
    cudaFree(d_src);
    cudaFree(d_dst);
	
    CImgDisplay main_disp(dst, "After Processing");
    while (!main_disp.is_closed())
        main_disp.wait();

    return 0;
}
