#include "ZoomList.h"

using namespace std;

namespace Fractals {

ZoomList::ZoomList(int w, int h) : Width(w), Height(h) {

}

void ZoomList::Add(const Zoom& zoom) {
    Zooms.push_back(zoom);

    xCenter += (zoom.x - Width / 2) * Scale;
    yCenter += (zoom.y - Height / 2) * Scale;

    Scale *= zoom.scale;
}

pair<double, double> ZoomList::ZoomIn(int x, int y) {
    double xFractal = (x - Width / 2) * Scale + xCenter;
    double yFractal = (y - Height / 2) * Scale + yCenter;

    return pair<double, double>(xFractal, yFractal);
}


}


