#include <fstream>
#include <iostream>

#include "Bitmap.h"
#include "BitmapFileHeader.h"
#include "BitmapInfoHeader.h"

using namespace Fractals;
using namespace std;

namespace Fractals {

Bitmap::Bitmap(int w, int h) :  Width(w), Height(h), pPixels(new uint8_t[w * h * 3]{}) /* the {} initializes the array elements to 0 */ {

}

Bitmap::~Bitmap() {

}

bool Bitmap::Write(string FileName) {
    BitmapFileHeader FileHeader;
    BitmapInfoHeader InfoHeader;

    FileHeader.FileSize = sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader) + Width * Height * 3;
    FileHeader.DataOffset = sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader);

    InfoHeader.Width = Width;
    InfoHeader.Height = Height;

    // open the file
    ofstream File;
    File.open(FileName, ios::out|ios::binary);
    if (!File) {
        cout << "Could not open file" << endl;
        return false;
    }

    // write to the file
    File.write((char*) &FileHeader, sizeof(FileHeader));
    File.write((char*) &InfoHeader, sizeof(InfoHeader));
    File.write((char*) pPixels.get(), Width * Height * 3); // Width * Height * 3 because we have 3 colours

    // close the file
    File.close();
    if (!File) {
        cout << "Could not close file" << endl;
        return false;
    }

    return true;
}

void Bitmap::SetPixel(int x, int y, uint8_t r, uint8_t g, uint8_t b) {

}

}