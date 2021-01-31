#ifndef IMAGE_H
#define IMAGE_H

#include "config.hpp"
#include <vector>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <fstream>


using namespace std;

class image{


public:
	string file_path;

    // Data
	unsigned char *data;
    int datasize;

    // Matrix
    int width;
    int height;
    unsigned char **matrix;

    image(string);
    ~image();
    void read();
    void to_matrix();
    void trim();


};


typedef struct {
    unsigned short type;              // Magic identifier: 0x4d42
    unsigned int size;              // File size in bytes
    unsigned short reserved1;         // Not used
    unsigned short reserved2;         // Not used
    unsigned int offset;            // Offset to image data in bytes from beginning of file
    unsigned int dib_header_size;   // DIB Header size in bytes
    int  width_px;          		// Width of the image
    int  height_px;         		// Height of image
    unsigned short num_planes;        // Number of color planes
    unsigned short bits_per_pixel;    // Bits per pixel
    unsigned int compression;       // Compression type
    unsigned int image_size_bytes;  // Image size in bytes
    int  x_resolution_ppm;  // Pixels per meter
    int  y_resolution_ppm;  // Pixels per meter
    unsigned int num_colors;        // Number of colors
    unsigned int important_colors;  // Important colors
} BMPHeader;





#endif

