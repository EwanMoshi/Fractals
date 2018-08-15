#ifndef MANDELBROT_H_
#define MANDELBROT_H_

namespace Fractals {

class Mandelbrot {
public:
    Mandelbrot();
    virtual ~Mandelbrot();

    static int GetIterations(double x, double y);

    // the number of iterations for each pixel
    static const int MAX_ITERATIONS = 1000;
};

}

#endif