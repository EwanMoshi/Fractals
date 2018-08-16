#include "RGB.h"

namespace Fractals {

RGB::RGB(double r, double g, double b) : r(r), g(g), b(b) {

}

RGB operator-(const RGB& A, const RGB& B) {
    return RGB(A.r - B.r, A.g - B.g, A.b - B.b);
}

}