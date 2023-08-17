/************************************************************************
**
** NAME:        gameoflife.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Justin Yokota - Starter Code
**				YOUR NAME HERE
**
**
** DATE:        2020-08-23
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "imageloader.h"

//Determines what color the cell at the given row/col should be. This function allocates space for a new Color.
//Note that you will need to read the eight neighbors of the cell in question. The grid "wraps", so we treat the top row as adjacent to the bottom row
//and the left column as adjacent to the right column.
Color *evaluateOneCell(Image *image, int row, int col, uint32_t rule)
{
	//YOUR CODE HERE
	Color *cell = (Color *) malloc (sizeof(Color));
        cell->R = image->image[row][col].R;
	cell->G = image->image[row][col].G;
	cell->B = image->image[row][col].B;
        for (uint32_t i=0; i < row; i++){
                for (uint32_t j=0; j < col; j++){
                        uint8_t blue = cell->B;
                        uint8_t bit = blue & 1;
                        if (bit == 1){
                                nextImage->image[i][j].R = 255;
                                nextImage->image[i][j].G = 255;
                        }
                        else{
                                nextImage->image[i][j].R = 0;
                                nextImage->image[i][j].G = 0;
                                nextImage->image[i][j].B = 0;
                        }
                }
        }
	return cell;
}

//The main body of Life; given an image and a rule, computes one iteration of the Game of Life.
//You should be able to copy most of this from steganography.c
Image *life(Image *image, uint32_t rule)
{
	//YOUR CODE HERE
	Image *nextImage = (Image *) malloc(sizeof(Image));
        uint32_t row = image->rows;
        uint32_t col = image->cols;
	nextImage->rows = row;
	nextImage->cols = col;	
	nextImage->image = (Color **) malloc(row*sizeof(Color *));
        Color *pixel;
	for (uint32_t i = 0; i < row; i++){
	        nextImage->image[i] = (Color *) malloc(col*sizeof(Color));
	}
	for (uint32_t i=0; i < row; i++){		
		for (uint32_t j=0; j < col; j++){
			pixel = evaluateOneCell(image,i,j,rule);
			uint8_t blue = pixel->B;
	                uint8_t bit = blue & 1;
			free(pixel);
			if (bit == 1){
				nextImage->image[i][j].R = 255;
				nextImage->image[i][j].G = 255;
				nextImage->image[i][j].B = 255;	   
	                }
			else{
				nextImage->image[i][j].R = 0;
				nextImage->image[i][j].G = 0;
				nextImage->image[i][j].B = 0;
	                }
		}
	}
	return nextImage;
}

/*
Loads a .ppm from a file, computes the next iteration of the game of life, then prints to stdout the new image.

argc stores the number of arguments.
argv stores a list of arguments. Here is the expected input:
argv[0] will store the name of the program (this happens automatically).
argv[1] should contain a filename, containing a .ppm.
argv[2] should contain a hexadecimal number (such as 0x1808). Note that this will be a string.
You may find the function strtol useful for this conversion.
If the input is not correct, a malloc fails, or any other error occurs, you should exit with code -1.
Otherwise, you should return from main with code 0.
Make sure to free all memory before returning!

You may find it useful to copy the code from steganography.c, to start.
*/
int main(int argc, char **argv)
{
	//YOUR CODE HERE
}
