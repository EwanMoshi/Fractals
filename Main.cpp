#include <iostream>

#include "FractalMaker.h"
#include "RGB.h"
#include "Zoom.h"

using namespace std;
using namespace Fractals;

int main() {
    FractalMaker FractalMaker(800, 600);

    // add color range
    FractalMaker.AddColorRange(RGB(255, 0, 0), 0.0);
    FractalMaker.AddColorRange(RGB(255, 255, 0), 0.3);
    FractalMaker.AddColorRange(RGB(0, 255, 0), 0.5);
    FractalMaker.AddColorRange(RGB(255, 255, 255), 1.0);

    // zoom in on arbitrary points
    FractalMaker.AddZoom(Zoom(295, 202, 0.1));
    // FractalMaker.AddZoom(Zoom(312, 304, 0.1));
    // FractalMaker.AddZoom(Zoom(400, 300, 0.1));
    // FractalMaker.AddZoom(Zoom(300, 300, 0.1));

    FractalMaker.Run("MandelbrotFractal.bmp");

    cout << "Finished Writing" << endl;
    return 0;
}