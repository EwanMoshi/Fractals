#ifndef FRACTALMAKER_H_
#define FRACTALMAKER_H_

#include <string>
#include "Zoom.h"

using namespace std;

namespace Fractals {

class FractalMaker {
public:
    FractalMaker(int w, int h);
    virtual ~FractalMaker();

    void CalculateIteration();
    void DrawFractal();
    void WriteBitmap(string FileName);
    void AddZoom(const Zoom& Zoom);
};

}

#endif