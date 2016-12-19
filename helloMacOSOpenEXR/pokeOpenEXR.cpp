//
//  pokeOpenEXR.cpp
//  hellloOpenEXRMacOS
//
//  Created by Douglass Turner on 12/17/16.
//  Copyright © 2016 Elastic Image Software. All rights reserved.
//

#include <iostream>
#include <macOSOpenEXRLibrary/OpenEXRConfig.h>
#include <macOSOpenEXRLibrary/ImfRgbaFile.h>
#include <macOSOpenEXRLibrary/ImfStringAttribute.h>
#include <macOSOpenEXRLibrary/ImfMatrixAttribute.h>
#include <macOSOpenEXRLibrary/ImfArray.h>
#include <macOSOpenEXRLibrary/ImathBox.h>

using namespace std;
using namespace Imf;
using namespace Imath;

void readRgba (const char fileName[], Array2D<Rgba> &pixels);

extern "C" void pokeOpenEXR(const char *exrFileName, long* width, long* height) {

    Array2D<Rgba> fileContents;
    readRgba(exrFileName, fileContents);
    *width = fileContents.width();
    *height = fileContents.height();
    
}

void readRgba (const char fileName[], Array2D<Rgba> &pixels) {
    //
    // Read an RGBA image using class RgbaInputFile:
    //
    //	- open the file
    //	- allocate memory for the pixels
    //	- describe the memory layout of the pixels
    //	- read the pixels from the file
    //

    RgbaInputFile file (fileName);
    Box2i dw = file.dataWindow();

    int width  = dw.max.x - dw.min.x + 1;
    int height = dw.max.y - dw.min.y + 1;
    pixels.resizeErase (height, width);

    file.setFrameBuffer (&pixels[0][0] - dw.min.x - dw.min.y * width, 1, (size_t) width);
    file.readPixels (dw.min.y, dw.max.y);

}
