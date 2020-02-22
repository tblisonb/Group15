//
//  QuickRunViewController.swift
//  CoilWind
//
//  Created by Zane Guess on 2/21/20.
//  Copyright © 2020 Capstone Team 15. All rights reserved.
//


import Foundation
import UIKit

class QuickRunViewController: UIViewController, UITextFieldDelegate, UIPickerViewDelegate,
UINavigationControllerDelegate, UIPickerViewDataSource{
    
    
    // text field variables
    @IBOutlet weak var nameTV: UITextField!
    @IBOutlet weak var colorTV: UITextField!
    @IBOutlet weak var lengthTV: UITextField!
    @IBOutlet weak var quantityTV: UITextField!    
    @IBOutlet weak var gaugeTV: UITextField!
    
    
    // label variables
    @IBOutlet weak var quickRunLabel: UILabel!
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

        gaugePicker.delegate = self
        self.gaugePicker.dataSource = self
        //set up picker
        gaugePicker.removeFromSuperview()
        gaugeTV.inputView = gaugePicker
        
        // convert the [double] of values to string so the picker view can display
        self.gaugeNameForPicker = doubleArraytoStringArray(gaugePickerRange: gaugePickerRange)

        let crs:[String] = selectedGauge.components(separatedBy: " ")
        gaugeTV.text = crs[0]
        
        print(gaugePickerRange.count)
        
        print("in quickrun")
        
        }
    
    func doubleArraytoStringArray (gaugePickerRange: [Double])-> [String] {
        var stringValue:String = ""
        print("in converting array")
        for num in gaugePickerRange{
            stringValue = String(format: "%.02f",num)
            print(stringValue)
            gaugeNameForPicker.append(stringValue)
        }
        return gaugeNameForPicker
    }
    
    // run device button ----- unable to finish at this time
    // will finish once bluetooth functionality is implemented
    @IBAction func runDeviceBtn(_ sender: Any) {
    }
    
    // quick save button implements add function to database
    @IBAction func quickSaveBtn(_ sender: Any) {
        let saveName:String = nameTV.text!
        let saveColor:String = colorTV.text!
        let saveLength:Double = NumberFormatter().number(from: (lengthTV.text)!) as! Double
        let saveGauge:Double = NumberFormatter().number(from: (gaugeTV.text)!) as! Double
        let saveQuantity:Int = NumberFormatter().number(from: (quantityTV.text)!) as! Int
        
        
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
        
        
        let coilDB = CoilCoreDataDB()
        let ret = coilDB.addCoil(saveName, color: saveColor, length: saveLength, gauge: saveGauge, quantity: saveQuantity)
        _ = coilDB.saveContext()
        print(coilDB.getCoil(saveName).length)
         print("coil \(saveName) added. Add coil return is: \(ret)")
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

    
    
    
    
    
    
}
