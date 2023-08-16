/************************************************************************
**
** NAME:        steganography.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**				Justin Yokota - Starter Code
**				YOUR NAME HERE
**
** DATE:        2020-08-23
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "imageloader.h"

//Determines what color the cell at the given row/col should be. This should not affect Image, and should allocate space for a new Color.
Color *evaluateOnePixel(Image *image, int row, int col)
{
	//YOUR CODE HERE
	Color *px = (Color *) malloc (sizeof(Color));
	px->R = image->image[row][col].R;
	px->G = image->image[row][col].G;
	px->B = image->image[row][col].B;
	return px;
}

//Given an image, creates a new image extracting the LSB of the B channel.
Image *steganography(Image *image)
{
	//YOUR CODE HERE
	Image *secretImage = (Image *) malloc(sizeof(Image));
        uint32_t row = image->rows;
        uint32_t col = image->cols;
	secretImage->rows = row;
	secretImage->cols = col;	
	secretImage->image = (Color **) malloc(row*sizeof(Color *));
        Color *pixel;
	for (uint32_t i = 0; i < image->rows; i++){
	        secretImage->image[i] = (Color *) malloc(col*sizeof(Color));
	}
	for (uint32_t i=0; i < row; i++){		
		for (uint32_t j=0; j < col; j++){
			pixel = evaluateOnePixel(image,i,j);
			uint8_t blue = pixel->B;
	                uint8_t bit = blue & 1;
			free(pixel);
			if (bit == 1){
				secretImage->image[i][j].R = 255;
				secretImage->image[i][j].G = 255;
				secretImage->image[i][j].B = 255;	   
	                }
			else{
				secretImage->image[i][j].R = 0;
				secretImage->image[i][j].G = 0;
				secretImage->image[i][j].B = 0;
	                }
		}
	}
	return secretImage;
}

/*
Loads a file of ppm P3 format from a file, and prints to stdout (e.g. with printf) a new image, 
where each pixel is black if the LSB of the B channel is 0, 
and white if the LSB of the B channel is 1.

argc stores the number of arguments.
argv stores a list of arguments. Here is the expected input:
argv[0] will store the name of the program (this happens automatically).
argv[1] should contain a filename, containing a file of ppm P3 format (not necessarily with .ppm file extension).
If the input is not correct, a malloc fails, or any other error occurs, you should exit with code -1.
Otherwise, you should return from main with code 0.
Make sure to free all memory before returning!
*/
int main(int argc, char **argv)
{
	//YOUR CODE HERE
	if (argc != 2){
		printf("usage: %s filename\n",argv[0]);
		printf("filename is an ASCII PPM file (type P3) with maximum value 255.\n");
		exit(-1);
	}
        Image *image;
	Image *targetImage;
        char *filename;
        filename = argv[1];
        image = readData(filename);
        targetImage = steganography(image);
        writeData(targetImage);
        freeImage(image);
	freeImage(targetImage);
        return 0;	
}
