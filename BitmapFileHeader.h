#ifndef BITMAPFILEHEADER_H_
#define BITMAPFILEHEADER_H_

#include <cstdint>

using namespace std;

// align 2 bytes boundary for struct
#pragma pack(2)

namespace Fractals {

struct BitmapFileHeader {
    char header[2]{'B', 'M'};
    int32_t FileSize;
    int32_t Reserved{0};
    int32_t DataOffset;
};

}



#endif // BITMAPFILEHEADER_H_