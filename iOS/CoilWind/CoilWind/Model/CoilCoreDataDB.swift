//
//  CoilCoreDataDB.swift
//  CoilWind
//
//  Database functions class 
//
//
//  Created by Zane Guess on 2/21/20.
//  Copyright © 2020 Capstone Team 15. All rights reserved.
//  @version 1.0



import UIKit
import Foundation
import CoreData

// data base class
public class CoilCoreDataDB{
    
    var appDel:AppDelegate?
    var mContext:NSManagedObjectContext?
    
    // initialize the database
    init(){
        appDel = (UIApplication.shared.delegate as! AppDelegate)
        mContext = appDel!.persistentContainer.viewContext
    }
    
    // check whether a coil setting exists in the data storage
    func coilExists(withName:String)->Bool {
        var ret:Bool = false
        let selectRequest:NSFetchRequest<Coil> = Coil.fetchRequest()
        selectRequest.predicate = NSPredicate(format:"name == %@",withName)
        
        // checking if the name exists in database
        do{
            let results = try mContext!.fetch(selectRequest)
            if results.count > 0 {
                ret = true
            }
        } catch let error as NSError{
            NSLog("Error selecting coil \(withName). Error: \(error)")
        }
        return ret
    }
    
    // get array of all names in the data base
    func getNames() -> [String] {
        var ret:[String] = [String]()
        let fetchStuds:NSFetchRequest<Coil> = Coil.fetchRequest()
        do{
            let results = try mContext!.fetch(fetchStuds)
            for aCoil in results {
                ret.append((aCoil as AnyObject).value(forKey:"name") as! String)
            }
        } catch let error as NSError {
            print("error selecting all coils: \(error)")
        }
        return ret.sorted()
    }
    
    // add a coil setting to the database
    func addCoil(_ name:String, color:String, length:Double, gauge:Double, quantity:Int) -> Bool {
        var ret:Bool = false
        if !coilExists(withName: name) {
            let entity = NSEntityDescription.entity(forEntityName: "Coil", in: mContext!)
            let aCoil = NSManagedObject(entity: entity!, insertInto: mContext)
            aCoil.setValue(name, forKey:"name")
            aCoil.setValue(color, forKey:"color")
            aCoil.setValue(length, forKey:"length")
            aCoil.setValue(gauge, forKey:"gauge")
            aCoil.setValue(quantity, forKey:"quantity")
            
            
            ret = true
        }
        return ret
    }
    

    
//    func convertToJSONArray(moArray: [NSManagedObject]) -> Any {
//        var jsonArray: [[String: Any]] = []
//        for item in moArray {
//            var dict: [String: Any] = [:]
//            for attribute in item.entity.attributesByName {
//                //check if value is present, then add key to dictionary so as to avoid the nil value crash
//                if let value = item.value(forKey: attribute.key) {
//                    dict[attribute.key] = value
//                }
//            }
//            jsonArray.append(dict)
//        }
//        return jsonArray
//    }
    

    // get a specific coil setting from data base with all associated description values of the coil
    func getCoil(_ name:String) -> (name:String, color:String, length:Double, gauge:Double, quantity:Int) {
        
        var aCoil:(name:String, color:String, length:Double, gauge:Double, quantity:Int) = ("name","",0.0,0.0,0)
        
        let fetchACoil:NSFetchRequest<Coil> = Coil.fetchRequest()
        fetchACoil.predicate = NSPredicate(format:"name == %@",name)
        do{
            let results = try mContext!.fetch(fetchACoil)
            if results.count > 0 {
                let color = (results[0] as AnyObject).value(forKey: "color") as? String
                let length = (results[0] as AnyObject).value(forKey: "length") as? Double
                let gauge = (results[0] as AnyObject).value(forKey: "gauge") as? Double
                let quantity = (results[0] as AnyObject).value(forKey: "quantity") as? Int

                
                aCoil = (name,color,length,gauge,quantity) as! (name: String, color: String, length: Double, gauge: Double, quantity: Int)
            }
        }catch let error as NSError{
            print("error getting coil \(name), error \(error)")
        }
        return aCoil
    }
    
 
    

    // delete Coil setting from data base
    func deleteCoil(name:String) -> Bool {
        var ret:Bool = false
        let selectRequest:NSFetchRequest<Coil> = Coil.fetchRequest()
        selectRequest.predicate = NSPredicate(format:"name == %@",name)
        do{
            let results = try mContext!.fetch(selectRequest)
            if results.count > 0 {
                mContext!.delete(results[0] as NSManagedObject)
                //try mContext?.save()
                ret = true
            }
        } catch let error as NSError{
            NSLog("error deleting coil \(name). Error \(error)")
        }
        return ret
    }

    
    // save the context of the database
    func saveContext() -> Bool {
        var ret:Bool = false
        do{
            try mContext!.save()
            ret = true
        }catch let error as NSError{
            print("error saving context \(error)")
        }
        return ret
    }
}
