#ifndef pixel_h
#define pixel_h

#include <stdio.h>

// Represents a single pixel in the image
class Pixel {
private:
    int x;                  // horizontal location
    int y;                  // vertical location
    unsigned int value;     // shade of grey
    bool marked;            // indicates if this pixel has been counted
    
public:
    Pixel(int x = 0, int y = 0, unsigned int value = 0, bool marked = false) {
        this->x = x;
        this->y = y;
        this->value = value;
        this->marked = marked;
    }
    
    int getX() const { return x; }
    int getY() const { return y; }
    int getValue() const { return value; }
    
    bool getMarked() const { return marked; }
    void setMarked(bool marked) { this->marked = marked; }
};

#endif
