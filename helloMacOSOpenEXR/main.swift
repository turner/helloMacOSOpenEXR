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

let filename:String = "dusk.exr"
pokeOpenEXR(filename, wp, hp)

let width = wp.pointee
let height = hp.pointee

print("file \(filename) width \(width) height \(height)\n")


