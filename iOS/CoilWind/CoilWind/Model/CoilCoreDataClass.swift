//
//  CoilCoreDataClass.swift
//  CoilWind
//
//  Created by Zane Guess on 2/21/20.
//  Copyright © 2020 Capstone Team 15. All rights reserved.
//


import Foundation
import CoreData

@objc(Coil)
public class Coil: NSManagedObject {
    
    struct coil:Encodable {
        var name: String?
        var color: String?
        var gauge: Int
        var length: Int
        var quantity: Int

    }
    
    struct sendCoil:Encodable{
        var gauge: Int
        var length: Int
        var quantity: Int
    }
}
