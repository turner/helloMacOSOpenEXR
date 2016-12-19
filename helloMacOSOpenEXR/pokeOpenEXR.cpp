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
void readHeader (const char fileName[]);

extern "C" void pokeOpenEXR(const char *exrFileName) {

    readHeader(exrFileName);

    Array2D<Rgba> fileContents;
    readRgba(exrFileName, fileContents);
    
    cout << "fileContents(" << fileContents.width() << ", " << fileContents.height() << ")" << endl;
    
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

void readHeader (const char fileName[]) {
    //
    // Read an image's header from a file, and if the header
    // contains comments and camera transformation attributes,
    // print the values of those attributes.
    //
    //	- open the file
    //	- get the file header
    //	- look for the attributes
    //

    RgbaInputFile file (fileName);

    const StringAttribute *comments = file.header().findTypedAttribute <StringAttribute> ("comments");

    const M44fAttribute *cameraTransform = file.header().findTypedAttribute <M44fAttribute> ("cameraTransform");

    if (comments) {
        cout << "comments\n   " << comments->value() << endl;
    }

    if (cameraTransform) {
        cout << "cameraTransform\n" << cameraTransform->value() << flush;
    }

}
