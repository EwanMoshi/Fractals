#ifndef ZOOM_H_
#define ZOOM_H_

namespace Fractals {

struct Zoom {
    Zoom(int x, int y, double scale) : x(x), y(y), scale(scale) {
        
    };

    // zoom coordinates
    int x = 0;
    int y = 0;
    double scale = 0.0;
};

}

#endif