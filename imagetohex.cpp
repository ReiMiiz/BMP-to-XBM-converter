#include <stdint.h>
#include <iostream>
#include <cstdio>
#include <iomanip>
#define STB_IMAGE_IMPLEMENTATION
#include "stb-master/stb_image.h"

using namespace std;

int color1, color2;


int main() {
	ios_base::sync_with_stdio(false);

    int width = 0, height = 0, bpp, byteWidth;
    uint8_t* rgb_image = stbi_load("D:\\MCU Proj\\Ouroboros.bmp", &width, &height, &bpp, 1);
	
	byteWidth = width / 8;
	if(byteWidth*8 < width) byteWidth++;
	int img[height][byteWidth*8] = {0};
	uint8_t xbm[height*byteWidth];
	printf("seg: %d | real Width: %d | xbm Width: %d | bpp: %d\n", byteWidth, width, byteWidth*8, bpp);
	
	int cThreshold = 10;
	bool invert = false;
	color1 = invert ? 1 : 0;
	color2 = invert ? 0 : 1;
	
	for(int i = 0; i < height; i++){
		for(int j = 0; j < width; j++){
			//if((rgb_image[(i*width)+j] <= cThreshold) && (rgb_image[(i*width)+j+1] <= cThreshold) && (rgb_image[(i*width)+j+2] <= cThreshold)) img[i][j] = color1;
			if(rgb_image[(i*width)+j] <= cThreshold)img[i][j] = color1;
			else img[i][j] = color2;
			cout << " " << img[i][j];
		}
		cout << "\n";
	}
	
	printf("------------------------------------------\n");
	uint8_t pixval = 0;
	for(int i = 0; i < height; i++){
		for(int j = 0; j < byteWidth; j++){
			pixval += img[i][j*8];
			pixval += img[i][j*8 + 1]*2;
			pixval += img[i][j*8 + 2]*4;
			pixval += img[i][j*8 + 3]*8;
			pixval += img[i][j*8 + 4]*16;
			pixval += img[i][j*8 + 5]*32;
			pixval += img[i][j*8 + 6]*64;
			pixval += img[i][j*8 + 7]*128;
			printf("0x%.2x, ", pixval);
			pixval = 0;	
		}
		printf("\n");
	}
    stbi_image_free(rgb_image);
	
    return 0;
}