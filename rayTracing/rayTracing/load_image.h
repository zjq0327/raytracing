#pragma once
#define _CRT_SECURE_NO_WARNINGS


#include <cstdlib>
#include <iostream>

class rtw_image {
public:
    rtw_image() : data(nullptr) {}

    rtw_image(const char* image_filename);

    ~rtw_image();

    bool load(const std::string filename);

    int width()  const { return (data == nullptr) ? 0 : image_width; }
    int height() const { return (data == nullptr) ? 0 : image_height; }

    const unsigned char* pixel_data(int x, int y) const;


private:
    const int bytes_per_pixel = 3;
    unsigned char* data;
    int image_width, image_height;
    int bytes_per_scanline;

    static int clamp(int x, int low, int high) {
        // Return the value clamped to the range [low, high).
        if (x < low) return low;
        if (x < high) return x;
        return high - 1;
    }
};

