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
        
        //test problem with length
//        let db:CoilCoreDataDB = CoilCoreDataDB()
//        let aCoil = db.getCoil(coilNames[1])
//        print(aCoil.length)


        self.title = "Saved Coil List"
       
        
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
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
            
            viewController.selectedCoil = self.coilNames[indexPath.row]
            viewController.coilNames = self.coilNames
        }
    }
    
    
}



