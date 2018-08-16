#include "FractalMaker.h"

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
}


void FractalMaker::DrawFractal() {
    RGB StartColor(0, 00, 0);
    RGB EndColor(0, 0, 255);
    RGB ColorDiff = EndColor - StartColor;

   // draw the fractal
    for (int y = 0; y < Height; y++) {
        for (int x = 0; x < Width; x++) {
            uint8_t r = 0;
            uint8_t g = 0;
            uint8_t b = 0;
            
            int Iterations = FractalImage[y * Width + x];

            if (Iterations != Mandelbrot::MAX_ITERATIONS) {
                double Hue = 0.0;
                for (int i = 0; i <= Iterations; i++) {
                    Hue += static_cast<double>(Histogram[i]) / Total;
                }

                r = StartColor.r + ColorDiff.r * Hue;
                g = StartColor.g + ColorDiff.g * Hue;
                b = StartColor.b + ColorDiff.b * Hue;

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
}

}
