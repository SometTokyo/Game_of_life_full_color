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


unsigned get_bit(uint8_t x, unsigned n) {
    x >>= n;
    x  &= 1;
    return x;
}

void set_bit(uint8_t * x, unsigned n, unsigned v) {
    unsigned mask = ~(1<<n);
    *x = (*x & mask) | (v<<n);
}

void change_RGB(uint8_t *cellbit, uint32_t rule, uint32_t *nextState, uint8_t numOfNeighbors, unsigned n, uint8_t *color){
    *cellbit = get_bit(*color, n);
    if (*cellbit == 0) {
        *nextState = 1 & (rule >> numOfNeighbors);
    } else {
        *nextState = 1 & (rule >> (numOfNeighbors+9));
    }
    if (*nextState == 1) {
        set_bit(color, n, 1);
    } else {
        set_bit(color, n, 0);
    }
}

//Determines what color the cell at the given row/col should be. This function allocates space for a new Color.
//Note that you will need to read the eight neighbors of the cell in question. The grid "wraps", so we treat the top row as adjacent to the bottom row
//and the left column as adjacent to the right column.
Color *evaluateOneCell(Image *image, int row, int col, uint32_t rule)
{
    //YOUR CODE HERE
    Color *cell = (Color *) malloc(sizeof(Color));
    cell->R = image->image[row][col].R;
    cell->G = image->image[row][col].G;
    cell->B = image->image[row][col].B;

    uint8_t numOfNeighborsR = 0, numOfNeighborsG = 0, numOfNeighborsB = 0;
    uint32_t nextState;
    int x, y;
    int64_t x_temp, y_temp;
    uint8_t Rbit, Gbit, Bbit;
    uint8_t cellRbit, cellGbit, cellBbit;

    for (int n = 0; n < 8; n++) {
        for (x = row - 1; x <= row + 1; x++) {
            for (y = col - 1; y <= col + 1; y++) {
                if (x == row && y == col) {
                    continue;
                }
                //x_temp = (x + image->rows) % image->rows;
                //y_temp = (y + image->cols) % image->cols;
                x_temp = x;
                y_temp = y;
                if (x < 0) {
                    x_temp = image->rows - 1;
                }
                if (x > (int) image->rows - 1) {
                    x_temp = 0;
                }
                if (y < 0) {
                    y_temp = image->cols - 1;
                }
                if (y > (int) image->cols - 1) {
                    y_temp = 0;
                }

                Rbit = get_bit(image->image[x_temp][y_temp].R, n);
                if (Rbit) {
                    numOfNeighborsR++;
                }
                Gbit = get_bit(image->image[x_temp][y_temp].G, n);
                if (Gbit) {
                    numOfNeighborsG++;
                }
                Bbit = get_bit(image->image[x_temp][y_temp].B, n);
                if (Bbit) {
                    numOfNeighborsB++;
                }
            }
        }

        change_RGB(&cellRbit, rule, &nextState, numOfNeighborsR, n, &cell->R);
        change_RGB(&cellGbit, rule, &nextState, numOfNeighborsG, n, &cell->G);
        change_RGB(&cellBbit, rule, &nextState, numOfNeighborsB, n, &cell->B);        

        numOfNeighborsR = 0;
        numOfNeighborsG = 0;
        numOfNeighborsB = 0;
    }

    return cell;
}

//The main body of Life; given an image and a rule, computes one iteration of the Game of Life.
//You should be able to copy most of this from steganography.c
Image *life(Image *image, uint32_t rule)
{
    //YOUR CODE HERE
    Image *newImage = (Image *) malloc(sizeof(Image));
    newImage->rows = image->rows;
    newImage->cols = image->cols;
    newImage->image = (Color **) malloc(newImage->rows*sizeof(Color *));

    Color *pixel;
    for (uint32_t i = 0; i < image->rows; i++){
        newImage->image[i] = (Color *) malloc(newImage->cols*sizeof(Color));
    }

    for (int i=0; i < newImage->rows; i++){
        for (int j=0; j < newImage->cols; j++){
            pixel = evaluateOneCell(image,i,j,rule);
            newImage->image[i][j] = *pixel;
            free(pixel);
        }
    }

    return newImage;
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
    if (argc != 3){
        printf("usage: %s filename\n",argv[0]);
        printf("filename is an ASCII PPM file (type P3) with maximum value 255.\n");
        printf("rule is a hex number beginning with 0x; Life is 0x1808.\n");
        exit(-1);
    }

    Image *image;
    Image *targetImage;
    char *filename;
    const char *rulename;
    char *endptr;
    uint32_t rule;

    filename = argv[1];
    rulename = argv[2];
    rule = strtol(rulename, &endptr, 16);
    image = readData(filename);
    targetImage = life(image,rule);
    writeData(targetImage);
    freeImage(image);
    freeImage(targetImage);

    return 0;
}


