#include "Mandelbrot.h"
#include <complex>

using namespace std;

namespace Fractals {

Mandelbrot::Mandelbrot() {

}

Mandelbrot::~Mandelbrot() {

}

/**
 * Applies the Mandelbrot algorithm
 */
int Mandelbrot::GetIterations(double x, double y) {
    complex<double> z = 0;
    complex<double> c(x, y);

    int Iterations = 0;

    while (Iterations < MAX_ITERATIONS) {
        z = z * z + c;

        // break loop if magnitude of z is > 2
        if (abs(z) > 2) {
            break;
        }

        Iterations++;
    }

    return Iterations;
}

}