#include <iostream>
#include <cstdint>

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

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            double xFractal = (x - WIDTH / 2 - 200) * 2.0 / HEIGHT;
            double yFractal = (y - HEIGHT / 2) * 2.0 / HEIGHT;

            int Iterations = Mandelbrot::GetIterations(xFractal, yFractal);

            uint8_t color = static_cast<uint8_t>(256 * static_cast<double>(Iterations) / Mandelbrot::MAX_ITERATIONS);
            
            color = color * color * color;

            bitmap.SetPixel(x, y, 0, color, 0);

            if (xFractal < min) {
                min = color;
            }

            if (xFractal > max ) {
                max = color;
            }
        }
    }

    cout << min << ", " << max << endl;

    bitmap.Write("test.bmp");

    cout << "Finished Writing" << endl;
    return 0;
}