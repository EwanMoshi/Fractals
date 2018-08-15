#ifndef BITMAPINFOHEADER_H_
#define BITMAPINFOHEADER_H_

#include <cstdint>

using namespace std;

// align 2 bytes boundary for struct
#pragma pack(2)

namespace Fractals {

struct BitmapInfoHeader {
     // total byes of this struct
    int32_t HeaderSize{40};

    // width and height of the bitmap
    int32_t Width;
    int32_t Height;

    int16_t Planes{1};

    // 1 byte for each colour (RGB)
    int16_t BitPerPixel{24};

    // we don't want compression
    int32_t Compression{0};

    int32_t DataSize{0};

    // resolution for the bitmap
    int32_t HorizontalResolution{2400};
    int32_t VerticalResolution{2400};

    int32_t Colors{0};
    int32_t ImportantColors{0};
};

}

#endif