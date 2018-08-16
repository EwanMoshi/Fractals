#ifndef ZOOMLIST_H_
#define ZOOMLIST_H_

#include <vector>
#include <utility>
#include "Zoom.h"

namespace Fractals {

class ZoomList {
public:
    ZoomList(int w, int h);
    void Add(const Zoom& zoom);
    std::pair<double, double> ZoomIn(int x, int y);

private:
    int Width;
    int Height;

    double xCenter = 0;
    double yCenter = 0;
    double Scale = 1.0;

    std::vector<Zoom> Zooms;
};

}

#endif