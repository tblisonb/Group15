//
//  QuickRunViewController.swift
//  CoilWind
// -------------------------------------------------------
// Quick run view controller allowing for quick entries
// to run device. also allows for the functionality
// to save to data base allowing the settings to be view in
// and accessed from the table view
//
// -------------------------------------------------------
//  Created by Zane Guess on 2/21/20.
//  Copyright © 2020 Capstone Team 15. All rights reserved.
//  @version 1.0


import Foundation
import UIKit
import CoreBluetooth


class QuickRunViewController: UIViewController, UITextFieldDelegate, UIPickerViewDelegate,
UINavigationControllerDelegate, UIPickerViewDataSource{
    
    var ble : BlueToothModel!

    
    // text field variables
    @IBOutlet weak var nameTV: UITextField!
    @IBOutlet weak var colorTV: UITextField!
    @IBOutlet weak var lengthTV: UITextField!
    @IBOutlet weak var quantityTV: UITextField!    
    @IBOutlet weak var gaugeTV: UITextField!
    
    
    // label variables
    @IBOutlet weak var nameLabel: UILabel!
    @IBOutlet weak var colorLabel: UILabel!
    @IBOutlet weak var lengthLabel: UILabel!
    @IBOutlet weak var quantityLabel: UILabel!
    @IBOutlet weak var gaugeLabel: UILabel!
    
    //picker variable
    @IBOutlet weak var gaugePicker: UIPickerView!
    
    // variables for picker
    var gaugePickerRange = Array(stride(from: 20.0, through: 32.0, by: 1.0))
    var gaugeNameForPicker:[String] = [String]()
    var selectedGauge:String = ""
    
    //view loading func
    override func viewDidLoad() {
        super.viewDidLoad()

        // the data source and delegates to populate the picker. allowing the values to show
        gaugePicker.delegate = self
        self.gaugePicker.dataSource = self
        
        //set up picker
        gaugePicker.removeFromSuperview()
        gaugeTV.inputView = gaugePicker
        
        // convert the [double] of values to string so the picker view can display
        self.gaugeNameForPicker = doubleArraytoStringArray(gaugePickerRange: gaugePickerRange)

        // first index shows
        let crs:[String] = selectedGauge.components(separatedBy: " ")
        gaugeTV.text = crs[0]
        self.title = "Quick Run"
        
        }
    
    // convert [double] to [string] so that the picker will show values
    func doubleArraytoStringArray (gaugePickerRange: [Double])-> [String] {
        var stringValue:String = ""
        
        // for each double in array convert to string so that the picker will display

        for num in gaugePickerRange{
            stringValue = String(format: "%.02f",num)
            
            gaugeNameForPicker.append(stringValue)
        }
        return gaugeNameForPicker
    }
    
    // MARK: -- Run Device button to send the data to the wire cutting device.
    // no fully functional blocking mechanism has been completed at this time
    @IBAction func runDeviceBtn(_ sender: Any) {
        
        // get the values
        let sendLength:Double = NumberFormatter().number(from: (lengthTV.text)!) as! Double
        let sendGauge:Double = NumberFormatter().number(from: (gaugeTV.text)!) as! Double
        let sendQuantity:Int = NumberFormatter().number(from: (quantityTV.text)!) as! Int
        
        // serialize the data to be sent over bluetooth
        let sendCoil = Coil.sendCoil(gauge: sendGauge, length: sendLength, quantity: sendQuantity)
        let jsonData = (try? JSONEncoder().encode(sendCoil))!
        
        // test purposes to see the size of data packet to be sent
        print(jsonData)

        // test purposes to see what is being sent
        if let JSONString = String(data: jsonData, encoding: String.Encoding.utf8) {
           print(JSONString)
        }
        
        // send data packet over bluetooth
        ble.writeCoilCharacteristic(data: jsonData)
        
        

    }
    
    // quick save button implements add function to database
    @IBAction func quickSaveBtn(_ sender: Any) {
        
        // assign variables of values from text fields to be passed to database add function
        let saveName:String = nameTV.text!
        let saveColor:String = colorTV.text!
        let saveLength:Double = NumberFormatter().number(from: (lengthTV.text)!) as! Double
        let saveGauge:Double = NumberFormatter().number(from: (gaugeTV.text)!) as! Double
        let saveQuantity:Int = NumberFormatter().number(from: (quantityTV.text)!) as! Int
        
        // simple exception checking ***** Will need more indepth checks.
        if(saveName == ""){
            nameTV.text = "Enter a name"
        }
        if(saveColor == ""){
            colorTV.text = "enter a color"
        }
        if(saveLength == 0.0){
            lengthTV.text = String(format: "%.02f",5.0)
        }
        if(saveQuantity == 0){
            quantityTV.text = String(1)
        }
        if(saveGauge < gaugePickerRange[0] && saveGauge > gaugePickerRange[gaugeNameForPicker.count]){
            gaugeTV.text = gaugeNameForPicker[1]
        }
        
        // save the entry to database so that the table will populate with this entry
        let coilDB = CoilCoreDataDB()
        let ret = coilDB.addCoil(saveName, color: saveColor, length: saveLength, gauge: saveGauge, quantity: saveQuantity)
        _ = coilDB.saveContext()
        
        //***************************************************************************************************************************
        //serialize the entry test this will be moved to the run device button when the ble connection test have come back successful
        //***************************************************************************************************************************
        let aCoil = coilDB.getCoil(saveName)
        let aCoilJson = Coil.coil(name: aCoil.name, color:aCoil.color, gauge:aCoil.gauge, length: aCoil.length, quantity:aCoil.quantity)
        let sendCoil = Coil.sendCoil(gauge: aCoil.gauge, length: aCoil.length, quantity: aCoil.quantity)
        let jsonData = (try? JSONEncoder().encode(aCoilJson))!
        let jsonData2 = (try? JSONEncoder().encode(sendCoil))!
        
        print(jsonData2)
        
        if let JSONString = String(data: jsonData, encoding: String.Encoding.utf8) {
           print(JSONString)
        }
        //print(jsonData!)
        print("coil \(saveName) added. Add coil return is: \(ret)")
      
    }
    

    
    
    // touch events on this view
    override func touchesBegan(_ touches: Set<UITouch>, with event: UIEvent?) {
        self.gaugeTV.resignFirstResponder()
        view.endEditing(true)
        super.touchesBegan(touches, with: event)
    }

    // MARK: -- UITextFieldDelegate Method
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

    
    
    
    
    
    
}
