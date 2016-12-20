//
//  main.swift
//  helloMacOSOpenEXR
//
//  Created by Douglass Turner on 12/18/16.
//  Copyright © 2016 Elastic Image Software. All rights reserved.
//

import Foundation

let wp = UnsafeMutablePointer<CLong>.allocate(capacity: 1)
let hp = UnsafeMutablePointer<CLong>.allocate(capacity: 1)
let theBits:UnsafeMutablePointer<CUnsignedShort>

let filename:String = "dusk.exr"
theBits = pokeOpenEXR(filename, wp, hp)

let width = wp.pointee
let height = hp.pointee

print("file \(filename) width \(width) height \(height)\n")


let buffer = UnsafeBufferPointer(start: theBits, count: width * height);

for index in 0 ..< 8 {
    print("main \(index) \(buffer[ index ])\n")
}
