#include <iostream>
#include "Bitmap.h"

using namespace std;
using namespace Fractals;

int main() {
    Bitmap bitmap(800, 600);

    bitmap.Write("test.bmp");

    cout << "Finished Writing" << endl;
    return 0;
}