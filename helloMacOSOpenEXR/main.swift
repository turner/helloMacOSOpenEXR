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

//let filename:String = "red.exr"
let filename:String = "gourds.exr"
theBits = pokeOpenEXR(filename, wp, hp)

let width = wp.pointee
let height = hp.pointee

let length = 4 * width * height
let buffer = UnsafeBufferPointer(start: theBits, count: length);

print("unsigned short \(MemoryLayout<CUnsignedShort>.size)")

for index in 0 ..< 4 * width {
    print("main \(index) \(buffer[ index ])")
}

print("file \(filename) width \(width) height \(height) length of bit buffer  \(buffer.count)\n")
