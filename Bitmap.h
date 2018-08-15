#ifndef BITMAP_H_
#define BITMAP_H_

#include <string>
#include <cstdint>
#include <memory>

using namespace std;

namespace Fractals {

class Bitmap {
public:
    Bitmap(int w, int h);
    virtual ~Bitmap();
    
    bool Write(string FileName);
    void SetPixel(int x, int y, uint8_t r, uint8_t g, uint8_t b);

private:
    int Width = 0;
    int Height = 0;
    unique_ptr<uint8_t[]> pPixels = nullptr;

};

}

#endif