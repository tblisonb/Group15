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
    
    @IBOutlet weak var buttonPressLabel: UILabel!
    
    // label variables
    @IBOutlet weak var nameLabel: UILabel!
    @IBOutlet weak var colorLabel: UILabel!
    @IBOutlet weak var lengthLabel: UILabel!
    @IBOutlet weak var quantityLabel: UILabel!
    @IBOutlet weak var gaugeLabel: UILabel!
    
    //picker variable
    @IBOutlet weak var gaugePicker: UIPickerView!
    
    // variables for picker
    var gaugePickerRange = Array(stride(from: 20, through: 32, by: 1))
    var gaugeNameForPicker:[String] = [String]()
    var selectedGauge:String = ""
    
    //view loading func
    override func viewDidLoad() {
        super.viewDidLoad()
        print("in quick run")
        
        print(ble.deviceName)
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
    func doubleArraytoStringArray (gaugePickerRange: [Int])-> [String] {
        var stringValue:String = ""
        
        // for each double in array convert to string so that the picker will display

        for num in gaugePickerRange{
            stringValue = String(num)
            
            gaugeNameForPicker.append(stringValue)
        }
        return gaugeNameForPicker
    }
    
    // MARK: -- Run Device button to send the data to the wire cutting device.
    // no fully functional blocking mechanism has been completed at this time
    @IBAction func runDeviceBtn(_ sender: Any) {
        
        // get the values
        let sendLength:Int = NumberFormatter().number(from: (lengthTV.text)!) as! Int
        let sendGauge:Int = NumberFormatter().number(from: (gaugeTV.text)!) as! Int
        let sendQuantity:Int = NumberFormatter().number(from: (quantityTV.text)!) as! Int
        
        // serialize the data to be sent over bluetooth
        let sendCoil = Coil.sendCoil(gauge: sendGauge, length: sendLength, quantity: sendQuantity)
        let jsonData = (try? JSONEncoder().encode(sendCoil))!
        
        // test purposes to see the size of data packet to be sent
        print(jsonData)
        buttonPressLabel.text = "Device is running. Please wait for cycle to finish before hitting run again!"

        // test purposes to see what is being sent
        if let JSONString = String(data: jsonData, encoding: String.Encoding.utf8) {
           print(JSONString)
        }
        
        // "{\gauge\":25,\"quantity\":21,\"length\":32}"
        // send data packet over bluetooth
        ble.writeCoilCharacteristic(data: jsonData)
        
        

    }
    
    // quick save button implements add function to database
    @IBAction func quickSaveBtn(_ sender: Any) {
        
        // assign variables of values from text fields to be passed to database add function
        let saveName:String = nameTV.text!
        let saveColor:String = colorTV.text!
        let saveLength:Int = NumberFormatter().number(from: (lengthTV.text)!) as! Int
        let saveGauge:Int = NumberFormatter().number(from: (gaugeTV.text)!) as! Int
        let saveQuantity:Int = NumberFormatter().number(from: (quantityTV.text)!) as! Int
        
        // simple exception checking ***** Will need more indepth checks.
        if(saveName == ""){
            nameTV.text = "Enter a name"
        }
        if(saveColor == ""){
            colorTV.text = "enter a color"
        }
        if(saveLength == 0){
            lengthTV.text = String(5)
        }
        if(saveQuantity == 0){
            quantityTV.text = String(1)
        }

        
        // save the entry to database so that the table will populate with this entry
        let coilDB = CoilCoreDataDB()
        let ret = coilDB.addCoil(saveName, color: saveColor, length: saveLength, gauge: saveGauge, quantity: saveQuantity)
        _ = coilDB.saveContext()
        
        let aCoil = coilDB.getCoil(saveName)
        print(aCoil)
        
        buttonPressLabel.text = "Saved to database!"
       
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
