#ifndef image_h
#define image_h

#include <stdio.h>
#include <vector>
#include "pixel.h"

using namespace std;

// Represents an image which consists of a number of pixels
class Image {
private:
    // pixel pointers stored in 2D vector
    vector<vector<Pixel*>> pixels;
    
    /**
    * get adjacent pixels around the specified one
    * @param pixel pointer to the target pixel
    * @returns a vector of adjacent pixels that are not out of boundary
    */
    vector<Pixel*> getPixelNeighbours(const Pixel* pixel);
    
    /**
    * based on the target pixel, find all pixels in that area
    * @param x x-coordinate value of the target pixel
    * @param y y-coordinate value of the target pixel
    * @param count return the count of pixels in the target area
    * @param value return the shade of grey of the target area
    */
    void visit(int x, int y, int& count, unsigned int& value);

    /**
    * based on the target pixel, find all pixels in that area (Recrusive Method)
    * @param x x-coordinate value of the target pixel
    * @param y y-coordinate value of the target pixel
    * @param count return the count of pixels in the target area
    * @param value return the shade of grey of the target area
    */
    void visitR(int x, int y, int& count, unsigned int& value);
    
public:
    // constructor
    Image(unsigned long width, unsigned long height);
    
    // destructor
    ~Image();
    
    /**
    * set pixels from the buffer read from file
    * @param buffer data read from file
    */
    void setPixels(const vector<unsigned int>& buffer);
    
    /**
    * count the numbers of areas of different shades of grey
    * @returns a vector of unsigned int representing the number of each area
    */
    vector<unsigned int> countAreas();
    
    /**
    * nubmer of pixels in horizontal direction
    * @returns unsigned long
    */
    unsigned long getWidth() const { return pixels.size(); }
    
    /**
    * nubmer of pixels in vertical direction
    * @returns unsigned long
    */
    unsigned long getHeight() const { return pixels[0].size(); }
};

#endif
