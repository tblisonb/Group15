//
//  CoilCoreDataProperties.swift
//  CoilWind
//
//  Created by Zane Guess on 2/21/20.
//  Copyright © 2020 Capstone Team 15. All rights reserved.
//


import Foundation
import CoreData


extension Coil {
    
    @nonobjc public class func fetchRequest() -> NSFetchRequest<Coil> {
        return NSFetchRequest<Coil>(entityName: "Coil")
    }
    
    private enum CodingKeys: String, CodingKey {
        case name, color, gauge, length, quantity
        
    }

    public func encode(to encoder: Encoder) throws {
        var container = encoder.container(keyedBy: CodingKeys.self)
        try container.encode(name, forKey: .name)
        try container.encode(color, forKey: .color)
        try container.encode(gauge, forKey: .gauge)
        try container.encode(length, forKey: .length)
        try container.encode(quantity, forKey: .quantity)
    }
    
    @NSManaged public var name: String?
    @NSManaged public var color: String?
    @NSManaged public var gauge: Int
    @NSManaged public var length: Int
    @NSManaged public var quantity: Int

    
}

