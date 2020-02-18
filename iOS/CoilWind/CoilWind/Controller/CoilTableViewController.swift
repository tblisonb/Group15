//
//  CoilTableViewController.swift
//  CoilWind
//
//  Created by Zane Guess on 2/18/20.
//  Copyright © 2020 Capstone Team 15. All rights reserved.
//

import Foundation

import UIKit

class CoilTableViewController: UITableViewController {
    
    // table view
//    @IBOutlet var placesTable: UITableView!
    
    
    // global variables
//    var urlString:String = "http://127.0.0.1:8080"
//    var pnames: [String] = [String]()
//
    
    //var places:[String:Place] = [String:Place]()
    
    
    // view did load
    override func viewDidLoad() {
        super.viewDidLoad()
        initializeCoreData()
        // by default the button does not appear must add in code!!!!
        //------------------------------------------------------------
        // add an edit button, which is handled by the table view editing forRowAt
        self.navigationItem.leftBarButtonItem = self.editButtonItem
        // place an add button on the right side of the nav bar for adding a student
        // call addStudent function when clicked.
        let addButton = UIBarButtonItem(barButtonSystemItem: UIBarButtonItem.SystemItem.add, target: self, action: #selector(CoilTableViewController.addCoil))
        self.navigationItem.rightBarButtonItem = addButton
        
        // obtain the values from the model
        self.updateModel()
        
        
        self.title = "Place List"
       
        
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
//        let db:PlaceCoreDB = PlaceCoreDB()
//        pnames = db.getNames().sorted()
//        self.tableView.reloadData()
    }
    
    

 
    // called with the Navigation Bar Add button (+) is clicked
    // adding a new place via an alert style prompt dialog
    @objc func addCoil() {
//        print("add place button clicked")
//
//        // message for adding a new student
//        let promptND = UIAlertController(title: "New Place", message: "Enter the place description you wish to add!", preferredStyle: UIAlertController.Style.alert)
//        // if the user cancels, we don't want to add a place so nil handler
//        promptND.addAction(UIAlertAction(title: "Cancel", style: UIAlertAction.Style.default, handler: nil))
//        // setup the OK action and provide a closure to be executed when/if OK selected
//        promptND.addAction(UIAlertAction(title: "OK", style: UIAlertAction.Style.default, handler: { (action) -> Void in
//
//            // providing default values if text is left blank in the prompts
//            // first defining the string values for the new place
//            let newPlaceName:String = (promptND.textFields?[0].text == "") ?
//                "unknown" : (promptND.textFields?[0].text)!
//            let newCat:String = (promptND.textFields?[1].text == "") ?
//                "unknown" : (promptND.textFields?[1].text)!
//            let newDes:String = (promptND.textFields?[2].text == "") ?
//                "unknown" : (promptND.textFields?[2].text)!
//            let newaddrT:String = (promptND.textFields?[3].text == "") ?
//                "unknown" : (promptND.textFields?[3].text)!
//            let newaddrS:String = (promptND.textFields?[4].text == "") ?
//                "unknown" : (promptND.textFields?[4].text)!
//
//            // defining the double values for the place
//            var newEle:Double = 0.0
//            if let myNumber = NumberFormatter().number(from: (promptND.textFields?[5].text)!) {
//                newEle = myNumber.doubleValue
//            }
//
//            var newLat:Double = 0.0
//            if let myNumber = NumberFormatter().number(from: (promptND.textFields?[6].text)!) {
//                newLat = myNumber.doubleValue
//            }
//
//            var newLon:Double = 0.0
//            if let myNumber = NumberFormatter().number(from: (promptND.textFields?[7].text)!) {
//                newLon = myNumber.doubleValue
//            }
//
//            // add the new place values to the collection of places, followed by sorting and saving the new updated list to the tableview
//            let placeDB = PlaceCoreDB()
//            let ret = placeDB.addPlace(newPlaceName, category: newCat, des: newDes, addrT: newaddrT, addrS: newaddrS, ele: newEle, lat: newLat, lon: newLon)
//            _ = placeDB.saveContext()
//            print("Place \(newPlaceName) added. Add place return is: \(ret)")
//            self.updateModel()
//            _ = self.navigationController?.popViewController(animated: true)
//        }))
//
//        // defining the textfields for the user to enter with a generic placeholder
//        promptND.addTextField(configurationHandler: {(textField: UITextField!) in
//            textField.placeholder = "Place Name"
//        })
//        promptND.addTextField(configurationHandler: {(textField: UITextField!) in
//            textField.placeholder = "Place Category"
//        })
//        promptND.addTextField(configurationHandler: {(textField: UITextField!) in
//            textField.placeholder = "Place Description"
//        })
//        promptND.addTextField(configurationHandler: {(textField: UITextField!) in
//            textField.placeholder = "Address Title for Place"
//        })
//        promptND.addTextField(configurationHandler: {(textField: UITextField!) in
//            textField.placeholder = "Street Address of Place"
//        })
//        promptND.addTextField(configurationHandler: {(textField: UITextField!) in
//            textField.placeholder = "Place's elevation"
//        })
//        promptND.addTextField(configurationHandler: {(textField: UITextField!) in
//            textField.placeholder = "Place's Latitude"
//        })
//        promptND.addTextField(configurationHandler: {(textField: UITextField!) in
//            textField.placeholder = "Place's Longitude"
//        })
//        present(promptND, animated: true, completion: nil)
    }
    
    // MARK: - Table view data source
    
    // Support editing of the table view. Note, edit button must have been added
    // to the navigationitem (in this case left side) explicitly (view did load)
    override func tableView(_ tableView: UITableView, commit editingStyle: UITableViewCell.EditingStyle, forRowAt indexPath: IndexPath) {
//        print("tableView editing row at: \(indexPath.row)")
//        let selectedPlace:String = pnames[indexPath.row]
//
//        // remove name from database that way when updatemodel returns the array of place names it will not
//        // crash from out of bounds exceptions
//        if editingStyle == .delete {
//            print("deleting \(selectedPlace)")
//            let db:PlaceCoreDB = PlaceCoreDB()
//            let places = db.getPlace(selectedPlace).name
//            let ret = db.deletePlace(name: places)
//            _ = db.saveContext()
//
//
//            // reload data
//            self.updateModel()
//            print("resut of delete student \(ret)")
//        }
       

    }
    
    // MARK: - Table view data source methods
    override func numberOfSections(in tableView: UITableView) -> Int {
        return 1
    }
    
    // the number of rows in the table equals the count of the names array
//    override func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
//        //return self.pnames.count
//    }
    
    
    // configure what to display in each row cell
//    override func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
////        // Get and configure the cell...
////        print("loading table view")
////        let cell = tableView.dequeueReusableCell(withIdentifier: "PlacesCell", for: indexPath)
////        let db:PlaceCoreDB = PlaceCoreDB()
////        let des = db.getPlace(pnames[indexPath.row]).des
////        cell.textLabel?.text = pnames[indexPath.row]
////        cell.detailTextLabel?.text = des
////
// //       return cell
//    }
    
    
    
    // MARK: - Navigation
    // Storyboard seque: do any advance work before navigation, and/or pass data
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        super.prepare(for: segue, sender: sender)
        
        // prepping the the segue to include the relative data to be passed
//        if segue.identifier == "PlaceDetail" {
//            let viewController:ViewController = segue.destination as! ViewController
//            let indexPath = self.tableView.indexPathForSelectedRow!
//            print("resut of delete student \(pnames)")
//            viewController.selectedPlace = self.pnames[indexPath.row]
//            viewController.pnames = self.pnames
//        }
    }
    
    
}



