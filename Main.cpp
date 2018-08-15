#include <iostream>
#include <cstdint>
#include <memory>
#include <math.h>

#include "Bitmap.h"
#include "Mandelbrot.h"

using namespace std;
using namespace Fractals;

int main() {
    int const WIDTH = 800;
    int const HEIGHT = 600;

    Bitmap bitmap(WIDTH, HEIGHT);

    double min = 999999;
    double max = -999999;

    unique_ptr<int[]> Histogram(new int[Mandelbrot::MAX_ITERATIONS]{0});
    unique_ptr<int[]> FractalImage(new int[WIDTH * HEIGHT]{0});

    // store number of iterations per pixel
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            double xFractal = (x - WIDTH / 2 - 200) * 2.0 / HEIGHT;
            double yFractal = (y - HEIGHT / 2) * 2.0 / HEIGHT;

            int Iterations = Mandelbrot::GetIterations(xFractal, yFractal);
            
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

                green = pow(255, Hue);
            }


            bitmap.SetPixel(x, y, red, green, blue);

        }
    }


    bitmap.Write("MandelbrotFractal.bmp");

    cout << "Finished Writing" << endl;
    return 0;
}