//
//  wrapper.cpp
//  helloMacOSOpenEXR
//
//  Created by Douglass Turner on 12/18/16.
//  Copyright © 2016 Elastic Image Software. All rights reserved.
//

// extern "C" will cause the C++ compiler
// (remember, this is still C++ code!) to
// compile the function in such a way that
// it can be called from C
// (and Swift).

void pokeOpenEXR();

extern "C" void doit()
{
    pokeOpenEXR();
}
