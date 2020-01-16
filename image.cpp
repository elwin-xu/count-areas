#include "image.h"

/**
* get adjacent pixels around the specified one
* @param pixel pointer to the target pixel
* @returns a vector of adjacent pixels that are not out of boundary
*/
vector<Pixel*> Image::getPixelNeighbours(const Pixel* pixel) {
    vector<Pixel*> pixelNeighbour;
    
    // check if the adjacent pixels would be out of boundary
    // add the ones within the boundary to the vector
    if (pixel->getX() != pixels.size() - 1) {
        pixelNeighbour.push_back(pixels[pixel->getX() + 1][pixel->getY()]);
    }
    if (pixel->getX() != 0) {
        pixelNeighbour.push_back(pixels[pixel->getX() - 1][pixel->getY()]);
    }
    if (pixel->getY() != pixels[0].size() - 1) {
        pixelNeighbour.push_back(pixels[pixel->getX()][pixel->getY() + 1]);
    }
    if (pixel->getY() != 0) {
        pixelNeighbour.push_back(pixels[pixel->getX()][pixel->getY() - 1]);
    }
    
    return pixelNeighbour;
}

/**
* based on the target pixel, find all pixels in that area
* @param x x-coordinate value of the target pixel
* @param y y-coordinate value of the target pixel
* @param count return the count of pixels in the target area
* @param value return the shade of grey of the target area
*/
void Image::visit(int x, int y, int &count, unsigned int &value) {
    // find the target pixel
    Pixel* pixel = pixels[x][y];
    
    // initialise the return values
    count = 0;
    value = pixel->getValue();
    
    vector<Pixel*> stack;
    stack.push_back(pixel);
    
    while (stack.size() != 0) {
        Pixel* p = stack.back();
        
        // if p is marked, pop p to remove it from the stack
        if (p->getMarked()) {
            stack.pop_back();
            continue;
        }
        
        // otherwise, set it as marked
        p->setMarked(true);
        count++;
        
        // find adjacent pixels around the target one
        vector<Pixel*> pixelNeighbours = getPixelNeighbours(p);
        
        for (int i = 0; i < pixelNeighbours.size(); i++) {
            // *********** IMPORTANT NOTE ***************
            // if the neighbouring pixel is of the same colour and unmarked, push it to the stack
            // in the coming iterations, the adjacent pixels of these pushed ones will be further inspected
            // until the stack is empty, indicating all pixels within that area have been counted
            if (p->getValue() == pixelNeighbours[i]->getValue() && !pixelNeighbours[i]->getMarked())
            {
                stack.push_back(pixelNeighbours[i]);
            }
        }
    }
}

Image::Image(unsigned long width, unsigned long height) {
    // Initialisation
    pixels.resize(width);
    for (int i = 0; i < pixels.size(); i++) {
        pixels[i].resize(height);
    }
    
    // set all pixel pointers to nullptr
    for (int i = 0; i < pixels.size(); i++) {
        for (int j = 0; j < pixels[i].size(); j++) {
            pixels[i][j] = nullptr;
        }
    }
}

/**
* set pixels from the buffer read from file
* @param buffer data read from file
*/
void Image::setPixels(const vector<unsigned int> &buffer) {
    for (int i = 0; i < pixels.size(); i++) {
        for (int j = 0; j < pixels[i].size(); j++) {
            pixels[i][j] = new Pixel(i, j, buffer[i + j * pixels.size()]);
        }
    }
} 

/**
* count the numbers of areas of different shades of grey
* @returns a vector of unsigned int representing the number of each area
*/
vector<unsigned int> Image::countAreas() {
    vector<unsigned int> countAreas;
    countAreas.resize(256);
    
    // visit all pixels to find different areas
    for (int i = 0; i < pixels.size(); i++) {
        for (int j = 0; j < pixels[i].size(); j++) {
            int count;              // the count of pixels in the target area
            unsigned int value;     // the shade of grey of the target area
            
            // find the area that the target pixel belongs to
            visit(i, j, count, value);
            
            // if find another unmarked area, add 1 to the corresponding value
            if (count != 0) {
                countAreas[value]++;
            }
        }
    }
    
    return countAreas;
}

Image::~Image() {
    // Dynamically delete the pixels allocated earlier
    for (int i = 0; i < pixels.size(); i++) {
        for (int j = 0; j < pixels[i].size(); j++) {
            if (pixels[i][j] != nullptr) {
                delete pixels[i][j];
            }
        }
    }
}
