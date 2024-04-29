#include "load_image.h"


#ifdef _MSC_VER
#pragma warning (push, 0)
#endif

#define STB_IMAGE_IMPLEMENTATION
#define STBI_FAILURE_USERMSG
#include "external/stb_image.h"

rtw_image::rtw_image(const char* image_filename) {
    // Loads image data from the specified file. If the RTW_IMAGES environment variable is
    // defined, looks only in that directory for the image file. If the image was not found,
    // searches for the specified image file first from the current directory, then in the
    // images/ subdirectory, then the _parent's_ images/ subdirectory, and then _that_
    // parent, on so on, for six levels up. If the image was not loaded successfully,
    // width() and height() will return 0.

    auto filename = std::string(image_filename);
    auto imagedir = getenv("RTW_IMAGES");

    // Hunt for the image file in some likely locations.
    if (imagedir && load(std::string(imagedir) + "/" + image_filename)) return;
    if (load(filename)) return;
    if (load("images/" + filename)) return;
    if (load("../images/" + filename)) return;
    if (load("../../images/" + filename)) return;
    if (load("../../../images/" + filename)) return;
    if (load("../../../../images/" + filename)) return;
    if (load("../../../../../images/" + filename)) return;
    if (load("../../../../../../images/" + filename)) return;

    std::cerr << "ERROR: Could not load image file '" << image_filename << "'.\n";
}


rtw_image::~rtw_image() { STBI_FREE(data); }

bool rtw_image::load(const std::string filename) {
    // Loads image data from the given file name. Returns true if the load succeeded.
    auto n = bytes_per_pixel; // Dummy out parameter: original components per pixel
    data = stbi_load(filename.c_str(), &image_width, &image_height, &n, bytes_per_pixel);
    bytes_per_scanline = image_width * bytes_per_pixel;
    return data != nullptr;
}


// Restore MSVC compiler warnings
#ifdef _MSC_VER
#pragma warning (pop)
#endif