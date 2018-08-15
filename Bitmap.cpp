#include "Bitmap.h"

namespace Fractal {

Bitmap::Bitmap(int w, int h) :  Width(w), Height(h) {

}

Bitmap::~Bitmap() {

}

bool Bitmap::Write(string filename) {
    return false;
}


void Bitmap::SetPixel(int x, int y, uint8_t r, uint8_t g, uint8_t b) {
    
}

}