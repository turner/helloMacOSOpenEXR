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

extern "C" unsigned short * pokeOpenEXR(const char *exrFileName, long* width, long* height) {

    Array2D<Rgba> fileContents;
    readRgba(exrFileName, fileContents);
    *width = fileContents.width();
    *height = fileContents.height();
    
/*
    base + x * xStride + y * yStride.
    base, xStride, yStride are set to pixels, 1, width, respectively.
    pixel (x,y) is at memory address: pixels + (1 * x) + (width * y).
*/
    
    long yStride = 4 * fileContents.width();
    
    long r_offset = 0;
    long g_offset = 1;
    long b_offset = 2;
    long a_offset = 3;
    long index;
    
    unsigned short * rgbas = new unsigned short [4 * fileContents.width() * fileContents.height()];
    
    for (long y=0; y < fileContents.height(); y++) {
        
        long yOffset = y * yStride;
        for (long x=0; x < fileContents.width(); x++) {
            
            index = x + yOffset;
            rgbas[ r_offset + index ] = fileContents[ x ][ y ].r.bits();
            rgbas[ g_offset + index ] = fileContents[ x ][ y ].g.bits();
            rgbas[ b_offset + index ] = fileContents[ x ][ y ].b.bits();
            rgbas[ a_offset + index ] = fileContents[ x ][ y ].a.bits();
        }
    }
    
    for (long i=0; i < 8; i++) {
        cout << "pokeOpenEXR " << i << " " << rgbas[ i ] << endl;
    }
   
    return (unsigned short *)rgbas;
    
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
