#ifndef RGB_H_
#define RGB_H_

namespace Fractals {

struct RGB {
    RGB(double r, double g, double b);
    
    double r;
    double g;
    double b; 
};

RGB operator-(const RGB& A, const RGB& B);

}

#endif