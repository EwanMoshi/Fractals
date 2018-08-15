#ifndef BITMAP_H_
#define BITMAP_H_

#include <string>
#include <cstdint>

using namespace std;

namespace Fractal {

class Bitmap {
public:
    Bitmap(int w, int h);
    virtual ~Bitmap();
    
    bool Write(string filename);
    void SetPixel(int x, int y, uint8_t r, uint8_t g, uint8_t b);
private:
    int Width{0};
    int Height{0};
};

}

#endif