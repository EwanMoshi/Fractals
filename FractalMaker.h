#ifndef FRACTALMAKER_H_
#define FRACTALMAKER_H_

#include <string>
#include <cstdint>
#include <memory>
#include <math.h>
#include <vector>

#include "Zoom.h"
#include "Bitmap.h"
#include "Mandelbrot.h"
#include "ZoomList.h"
#include "RGB.h"

using namespace std;

namespace Fractals {

class FractalMaker {
public:
    FractalMaker(int w, int h);
    virtual ~FractalMaker();

    void Run(string Name);
    void AddZoom(const Zoom& Zoom);
    void AddColorRange(const RGB& color, double EndRange);

private:
    int Width;
    int Height;
    unique_ptr<int[]> Histogram;
    unique_ptr<int[]> FractalImage;
    Bitmap bitMap;
    ZoomList zoomList;
    int Total = 0;
    vector<int> Ranges;
    vector<RGB> Colors;
    vector<int> RangeTotals;
    
    bool bHasFirstRange = false;

    void CalculateIteration();
    void DrawFractal();
    void WriteBitmap(string FileName);
    void CalculateTotalIterations();
    void CalculateRangeTotals();
    int GetRange(int Iterations) const;
};

}

#endif