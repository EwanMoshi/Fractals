#include <iostream>
#include <cstdint>
#include <memory>
#include <math.h>

#include "Bitmap.h"
#include "Mandelbrot.h"
#include "ZoomList.h"
#include "FractalMaker.h"

using namespace std;
using namespace Fractals;

int main() {
    int const WIDTH = 800;
    int const HEIGHT = 600;

    Bitmap bitmap(WIDTH, HEIGHT);

    double min = 999999;
    double max = -999999;

    ZoomList Zoom_List(WIDTH, HEIGHT);
    Zoom_List.Add(Zoom(WIDTH / 2, HEIGHT / 2, 4.0 / WIDTH));
    Zoom_List.Add(Zoom(295, HEIGHT - 202, 0.1));
    Zoom_List.Add(Zoom(312, HEIGHT - 304, 0.1));

    unique_ptr<int[]> Histogram(new int[Mandelbrot::MAX_ITERATIONS]{0});
    unique_ptr<int[]> FractalImage(new int[WIDTH * HEIGHT]{0});

    // store number of iterations per pixel
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            pair<double, double> coords = Zoom_List.ZoomIn(x, y);
            
            int Iterations = Mandelbrot::GetIterations(coords.first, coords.second);
            
            FractalImage[y * WIDTH + x] = Iterations;

            // keep track of how many pixels have this number of Iterations
            if (Iterations != Mandelbrot::MAX_ITERATIONS) {
                Histogram[Iterations]++;
            }
        }
    }

    int Total = 0;
    for (int i = 0; i < Mandelbrot::MAX_ITERATIONS; i++) {
        Total += Histogram[i];
    }

    // draw the fractal
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            uint8_t red = 0;
            uint8_t green = 0;
            uint8_t blue = 0;
            
            int Iterations = FractalImage[y * WIDTH + x];

            if (Iterations != Mandelbrot::MAX_ITERATIONS) {
                double Hue = 0.0;
                for (int i = 0; i <= Iterations; i++) {
                    Hue += static_cast<double>(Histogram[i]) / Total;
                }

                green = Hue * 255;
            }


            bitmap.SetPixel(x, y, red, green, blue);

        }
    }


    bitmap.Write("MandelbrotFractal.bmp");

    cout << "Finished Writing" << endl;
    return 0;
}