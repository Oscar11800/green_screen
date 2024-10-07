// Author: Oscar Chen
// Sources: 
//      https://www.revelation.com/WebHelp/OI10_Presentation_Server_Object_Model/Image_transparency_-_Color-keying_and_Alpha-blending.htm
//      https://www.w3schools.com/c/c_arrays_multi.php
//      https://stackoverflow.com/questions/5162784/uint32-t-identifier-not-found-error
#include <stdint.h>
#include <stdio.h>


// Implement a blitting function which supports color-keyed transparency.

unsigned int const COLOR_KEY = 0xFF000000;

typedef struct PixelBuffer {
    // I changed pixels to pointer to a pointer for 2d in memory
    uint32_t **pixels;
    int width;
    int height;
}PixelBuffer;

// Copies the entire image from `src` into a destination buffer `dest`.
// The pixel buffers have a top-left origin and are row-major.
// `offsetX` and `offsetY` denote the origin within `dest` where `src` should be copied.
// Any pixel that exactly matches `COLOR_KEY` should be skipped.
// You may assume input buffers are pre-allocated and sufficiently large to complete the requested operation.
void blit(PixelBuffer const* src, PixelBuffer* dest, size_t offsetX, size_t offsetY) {
    // assuming input buffer are preallocated, no need to malloc or check
    // if I had to malloc, I'd have to do it twice for both src & dest by row & column

    // check that offsets are valid and stay with dest dimensions
    if(offsetX >= dest->width || offsetY >= dest->height){
        fprintf(stderr, "ERROR: Offset exceeds destination image dimensions\n");
        return;
    }

    // assuming that dest dimensions are preset
    // if size of src image exceeds offset dest dimensions then the image will be (effectively) cut off
    int max_height;
    int max_width;
   

    if(offsetY + src->height <= dest->height){
        max_height = src->height;
    } else{
        max_height = dest->height - offsetY;
    }

    if((offsetX + src->width) <= dest->width){
        max_width = src->width;
    } else{
        max_width = dest->width - offsetX;
    }

    // blit!! move! that! image!
    for(int i = 0; i < max_width; i++){
        for(int j = 0; j < max_height; j++){
            uint32_t pixel = src->pixels[i][j];
            if(pixel != COLOR_KEY){
                dest->pixels[i + offsetX][j + offsetY] = pixel;
            }
        }
    }
}