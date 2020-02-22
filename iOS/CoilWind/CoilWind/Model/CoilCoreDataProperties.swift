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
    
    @NSManaged public var name: String?
    @NSManaged public var color: String?
    @NSManaged public var gauge: Double
    @NSManaged public var length: Double
    @NSManaged public var quantity: Int

    
}

