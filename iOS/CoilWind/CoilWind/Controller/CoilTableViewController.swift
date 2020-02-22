//
//  CoilTableViewController.swift
//  CoilWind
//
//  Created by Zane Guess on 2/21/20.
//  Copyright © 2020 Capstone Team 15. All rights reserved.
//


import Foundation

import UIKit

class CoilTableViewController: UITableViewController {
    
    // table view

    //@IBOutlet var TableView: UITableView!
    
    
    // global variables
//    var urlString:String = "http://127.0.0.1:8080"
    var coilNames: [String] = [String]()
//
    
    //var places:[String:Place] = [String:Place]()
    
    
    // view did load
    override func viewDidLoad() {
        super.viewDidLoad()
        print("in table view")
 //       initializeCoreData()
        // by default the button does not appear must add in code!!!!
        //------------------------------------------------------------
        // add an edit button, which is handled by the table view editing forRowAt
        self.navigationItem.rightBarButtonItem = self.editButtonItem


        // obtain the values from the model
        self.updateModel()


        self.title = "Saved Coil List"
       
        
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    // initialize data base with a hard cored example for a few places.
    // this data will reset after the hard delete of the application from the simulator or device
    func initializeCoreData(){
//        let jsonPlace:[String] = ["{\"name\":\"ASU-WEST\", \"category\":\"School\", \"des\":\"Home of ASU's Applied Computing Program\", \"address_title\":\"ASU West Campus\", \"address_street\":\"13591 N 47th Ave$Phoenix AZ 85051\", \"elevation\":1100.0, \"latitude\":33.608979, \"longitude\":-112.159469}","{\"name\":\"UAK-Anchorage\", \"category\":\"School\", \"des\":\"University of Alaska's largest campus\", \"address_title\":\"University of Alaska at Anchorage\", \"address_street\":\"290 Spirit Dr$Anchorage AK 99508\", \"elevation\":0.0, \"latitude\":61.189748, \"longitude\":-149.826721}","{\"name\":\"Toreros\", \"category\":\"School\", \"des\":\"The University of San Diego, a private Catholic undergraduate university.\", \"address_title\":\"University of San Diego\", \"address_street\":\"5998 Alcala Park$San Diego CA 92110\", \"elevation\":200.0, \"latitude\":32.771923, \"longitude\":-117.188204}","{\"name\":\"New-York-NY\", \"category\":\"Travel\", \"des\":\"New York City Hall at West end of Brooklyn Bridge\", \"address_title\":\"New York City Hall\", \"address_street\":\"1 Elk St$New York NY 10007\", \"elevation\":2.0, \"latitude\":40.712991, \"longitude\":-74.005948}","{\"name\":\"Reavis-Grave\", \"category\":\"Hike\", \"des\":\"Grave site of Reavis Ranch Proprietor.\", \"address_title\":\"\", \"address_street\":\"\", \"elevation\":3900.0, \"latitude\":33.441499, \"longitude\":-111.182511}"]
//
//        // add the values to data base
//        do {
//            for aPlaceJson:String in jsonPlace {
//                let data:Data = aPlaceJson.data(using: String.Encoding.utf8)!
//                let dict:[String:Any] = try JSONSerialization.jsonObject(with: data, options: .mutableContainers) as! [String:Any]
//                let db:PlaceCoreDB = PlaceCoreDB()
//                if !db.placeExists(withName: dict["name"] as! String){
//                    _ = db.addPlace(dict["name"] as! String, category: dict["category"] as! String, des: dict["des"] as! String, addrT:  dict["address_title"] as! String, addrS: dict["address_street"] as! String, ele: dict["elevation"] as! Double, lat:  dict["latitude"] as! Double, lon: dict["longitude"] as! Double)
//
//
//                }
//                _ = db.saveContext()
//            }
//        }catch let error as NSError{
//            print("unable to add student. Error \(error)")
//        }
    }
    
    // update the model for viewing
    public func updateModel(){
        let db:CoilCoreDataDB = CoilCoreDataDB()
        coilNames = db.getNames().sorted()
        self.tableView.reloadData()
    }
    
    
    // MARK: - Table view data source
    
    // Support editing of the table view. Note, edit button must have been added
    // to the navigationitem (in this case left side) explicitly (view did load)
    override func tableView(_ tableView: UITableView, commit editingStyle: UITableViewCell.EditingStyle, forRowAt indexPath: IndexPath) {
        print("tableView editing row at: \(indexPath.row)")
        let selectedSavedCoil:String = coilNames[indexPath.row]

        // remove name from database that way when updatemodel returns the array of coil names it will not
        // crash from out of bounds exceptions
        if editingStyle == .delete {
            print("deleting \(selectedSavedCoil)")
            let db:CoilCoreDataDB = CoilCoreDataDB()
            let coil = db.getCoil(selectedSavedCoil).name
            let ret = db.deleteCoil(name: coil)
            _ = db.saveContext()


            // reload data
            self.updateModel()
            print("resut of delete saved coil \(ret)")
        }
       

    }
    
    // MARK: - Table view data source methods
    override func numberOfSections(in tableView: UITableView) -> Int {
        return 1
    }
    
    // the number of rows in the table equals the count of the names array
    override func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return self.coilNames.count
    }
    
    
    // configure what to display in each row cell
    override func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
       // Get and configure the cell...
        print("loading table view")
        
        // get the individual cell information
        let cell = tableView.dequeueReusableCell(withIdentifier: "CoilCell", for: indexPath)
        let db:CoilCoreDataDB = CoilCoreDataDB()
        let color = db.getCoil(coilNames[indexPath.row]).color
        cell.textLabel?.text = coilNames[indexPath.row]
        cell.detailTextLabel?.text = color

        return cell
    }
    
    
    
    // MARK: - Navigation
    // Storyboard seque: do any advance work before navigation, and/or pass data
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        super.prepare(for: segue, sender: sender)
        
        // prepping the the segue to include the relative data to be passed
        if segue.identifier == "SavedSettingSegue" {
            let viewController:CoilRunViewController = segue.destination as! CoilRunViewController
            let indexPath = self.tableView.indexPathForSelectedRow!
            print("resut of delete student \(coilNames)")
            viewController.selectedCoil = self.coilNames[indexPath.row]
            viewController.coilNames = self.coilNames
        }
    }
    
    
}



