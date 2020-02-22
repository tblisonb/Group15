//
//  CoilRunViewController.swift
//  CoilWind
//
//  Created by Zane Guess on 2/21/20.
//  Copyright © 2020 Capstone Team 15. All rights reserved.
//


import Foundation
import UIKit

class CoilRunViewController: UIViewController, UITextFieldDelegate, UIPickerViewDelegate,
UINavigationControllerDelegate, UIPickerViewDataSource{
    
    
    //Text field variables
    @IBOutlet weak var colorTV: UITextField!
    @IBOutlet weak var lengthTV: UITextField!
    @IBOutlet weak var quantityTV: UITextField!
    @IBOutlet weak var gaugeTV: UITextField!
    
    // label variables
    @IBOutlet weak var runDeviceLabel: UILabel!
    @IBOutlet weak var nameLabel: UILabel!
    @IBOutlet weak var colorLabel: UILabel!
    @IBOutlet weak var lengthLabel: UILabel!
    @IBOutlet weak var quantityLabel: UILabel!
    @IBOutlet weak var gaugeLabel: UILabel!
    
    // picker variables
    @IBOutlet weak var gaugePicker: UIPickerView!
    
    //NON EDITABLE VARIABLES
    @IBOutlet weak var savedNameLabel: UILabel!
    
    // variables
    var selectedCoil:String = ""
    var gaugePickerRange = Array(stride(from: 20.0, through: 32.0, by: 1.0))
    var gaugeNameForPicker:[String] = [String]()
    var selectedGauge:String = ""
    var coilNames: [String] = [String]()
    
    
    // on view did load function
        override func viewDidLoad() {
            super.viewDidLoad()
            
            print("in coil run view")
            self.populateUIFields(selectedCoil)
            
            // populate picker
            gaugePicker.delegate = self
            self.gaugePicker.dataSource = self
            
            //set up picker
            gaugePicker.removeFromSuperview()
            gaugeTV.inputView = gaugePicker
  
            // convert the [double] of values to string so the picker view can display
            self.gaugeNameForPicker = doubleArraytoStringArray(gaugePickerRange: gaugePickerRange)

  
            print(gaugePickerRange.count)
  
           
           
            
        }
    // convert [double] to [string] so that the picker will show values
    func doubleArraytoStringArray (gaugePickerRange: [Double])-> [String] {
        var stringValue:String = ""
       
        for num in gaugePickerRange{
            stringValue = String(format: "%.02f",num)
            
            gaugeNameForPicker.append(stringValue)
        }
        return gaugeNameForPicker
    }
    
    // Populate the text fields of this new view
    func populateUIFields(_ name:String){
        // instead of doing a query, could search the students array for the managed object.
        let db:CoilCoreDataDB = CoilCoreDataDB()
        let aCoil = db.getCoil(name)

        self.title = name
        savedNameLabel.text = "\(aCoil.name)"
        lengthTV.text = String(format: "%.02f",aCoil.length)
        gaugeTV.text = String(format: "%.02f",aCoil.gauge)
        quantityTV.text = String(aCoil.quantity)
        colorTV.text = "\(aCoil.color)"

        
    }
    
        // touch events on this view
           override func touchesBegan(_ touches: Set<UITouch>, with event: UIEvent?) {
               self.gaugeTV.resignFirstResponder()
           }
    //
    //       // MARK: -- UITextFieldDelegate Method
           func textFieldShouldReturn(_ textField: UITextField) -> Bool {
               self.gaugeTV.resignFirstResponder()
               return true
           }

           // MARK: -- UIPickerVeiwDelegate method
           // originally had it set so when the picker changed the selected place the GCDB would calculate upon the change
           // however due to the constraints the design choice was to remove this functionality and add to a button instead
           func pickerView(_ pickerView: UIPickerView, didSelectRow row: Int, inComponent component: Int) {
               selectedGauge = gaugeNameForPicker[row]
               
               let tokens:[String] = selectedGauge.components(separatedBy: " ")
               self.gaugeTV.text = tokens[0]
               
               self.gaugeTV.resignFirstResponder()
           }
           
           // UIPickerViewDelegate method
           func pickerView (_ pickerView: UIPickerView, titleForRow row: Int, forComponent component: Int) -> String? {
               let crs:String = gaugeNameForPicker[row]
               
               let tokens:[String] = crs.components(separatedBy: " ")
               return tokens[0]
           }
        
        // function for picker. number of components in the picker
        func numberOfComponents(in pickerView: UIPickerView) -> Int {
            return 1
    }

         // UIPickerviewDataSource method
        func pickerView(_ pickerView: UIPickerView, numberOfRowsInComponent component: Int) -> Int {
            return gaugeNameForPicker.count
    }
    
    // gets called when the coil description is modified to be saved as the new version of the table list so the edits save
    func navigationController(_ navigationController: UINavigationController, willShow viewController: UIViewController, animated: Bool){
        //print("entered navigationController willShow viewController")
        if let controller = viewController as? CoilTableViewController {
            let coilDB = CoilCoreDataDB()

            // first delete the current place from the list
            let deleteCoil = coilDB.deleteCoil(name: selectedCoil)
            print("Coil \(selectedCoil) deleted. delete coil return is: \(deleteCoil)")
            
            // obtain the values that remain in the various text fields
            let newName = savedNameLabel.text ?? ""
            let newColor = colorTV.text ?? ""
            let newLength: Double? = Double(lengthTV.text!)
            let newGauge: Double? = Double(gaugeTV.text!)
            let newQuantity: Int? = Int(quantityTV.text!)

            // pass the above saved values from the text field into the add method in the database to allow for the new modifications
            // this also works the same if no edits have been made.
            let ret = coilDB.addCoil(newName, color: newColor, length: newLength!, gauge: newGauge!, quantity: newQuantity!)
            _ = coilDB.saveContext()
            print("coil \(newName) added. Add coil return is: \(ret)")
            
            // added the edited values to the table so it saves state to database
            self.coilNames = Array(self.coilNames).sorted()

            // must reload table view with the updated place (if modified)
            // calls update model in the controller so that pnames can be update which
            // also for the index length to remain consistant allowing for scrolling and viewing of the table
            controller.updateModel()
        }
    }

    
    
   
    
    
    
    
}
