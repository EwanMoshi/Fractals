#include <iostream>
#include <assert.h>

#include "FractalMaker.h"

using namespace std;

namespace Fractals {

FractalMaker::FractalMaker(int w, int h) : Width(w), Height(h),
                                        Histogram(new int[Mandelbrot::MAX_ITERATIONS]{0}),
                                        FractalImage(new int[Width * Height]{0}),
                                        bitMap(Width, Height),
                                        zoomList(Width, Height) {
    zoomList.Add(Zoom(Width / 2, Height / 2, 4.0 / Width));
}

FractalMaker::~FractalMaker() {

}

void FractalMaker::Run(string name) {
    // calculate the iterations
    CalculateIteration();

    // calculate total iterations
    CalculateTotalIterations();

    // helper function
    CalculateRangeTotals();

    // draw the fractal image
    DrawFractal();

    // write the bitmap file
    WriteBitmap("MandelbrotFractal.bmp");
}

void FractalMaker::CalculateIteration() {
    // store number of iterations per pixel
    for (int y = 0; y < Height; y++) {
        for (int x = 0; x < Width; x++) {
            pair<double, double> coords = zoomList.ZoomIn(x, y);
            
            int Iterations = Mandelbrot::GetIterations(coords.first, coords.second);
            
            FractalImage[y * Width + x] = Iterations;

            // keep track of how many pixels have this number of Iterations
            if (Iterations != Mandelbrot::MAX_ITERATIONS) {
                Histogram[Iterations]++;
            }
        }
    }
}

void FractalMaker::CalculateTotalIterations() {
    for (int i = 0; i < Mandelbrot::MAX_ITERATIONS; i++) {
        Total += Histogram[i];
    }

    cout << "Total : " << Total << endl;
}


void FractalMaker::DrawFractal() {
   // draw the fractal
    for (int y = 0; y < Height; y++) {
        for (int x = 0; x < Width; x++) {
            int Iterations = FractalImage[y * Width + x];

            // find color range that we're in
            int Range = GetRange(Iterations);
            int RangeRotal = RangeTotals[Range];

            // get nubmer of iterations for the start range
            int RangeStart = Ranges[Range];

            // get the start and end color for this range
            RGB& StartColor = Colors[Range];
            RGB& EndColor = Colors[Range + 1];

            // get the color difference between the start and end color
            RGB ColorDifference = EndColor - StartColor;

            uint8_t r = 0;
            uint8_t g = 0;
            uint8_t b = 0;
            
            if (Iterations != Mandelbrot::MAX_ITERATIONS) {
                int TotalPixels = 0;

                for (int i = RangeStart; i <= Iterations; i++) {
                    TotalPixels += Histogram[i];
                }

                r = StartColor.r + ColorDifference.r * (double) TotalPixels / RangeRotal;
                g = StartColor.g + ColorDifference.g * (double) TotalPixels / RangeRotal;
                b = StartColor.b + ColorDifference.b * (double) TotalPixels / RangeRotal;
            }


            bitMap.SetPixel(x, y, r, g, b);
        }
    }
}

void FractalMaker::WriteBitmap(string FileName) {
    bitMap.Write(FileName);
}

void FractalMaker::AddZoom(const Zoom& Zoom) {
    zoomList.Add(Zoom);
}

void FractalMaker::AddColorRange(const RGB& color, double EndRange) {
    Colors.push_back(color);
    Ranges.push_back(EndRange * Mandelbrot::MAX_ITERATIONS);

    if (bHasFirstRange) {
        RangeTotals.push_back(0);
    }

    bHasFirstRange = true;


}

void FractalMaker::CalculateRangeTotals() {
    int Index = 0;

    for (int i = 0; i < Mandelbrot::MAX_ITERATIONS; i++) {
        int Pixels = Histogram[i];

        if (i >= Ranges[Index + 1]) {
            Index++;
        }

        RangeTotals[Index] += Pixels;
    }

    int overall = 0;

    for (int value : RangeTotals) {
        cout << "Range Total: " << value << endl;
        overall += value;
    }

    cout << "overall : " << overall << endl;
}

int FractalMaker::GetRange(int Iterations) const {
    int range = 0;

    // find the range for the given Iterations
    for (int i = 1; i < Ranges.size(); i ++) {
        range = i;

        if (Ranges[i] > Iterations) {
            break;
        }
    }

    range--;

    assert(range > -1);
    assert(range < Ranges.size());

    return range;
}


}
