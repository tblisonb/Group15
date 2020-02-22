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
    @IBOutlet weak var savedNameLabel: UILabel!
    @IBOutlet weak var colorLabel: UILabel!
    @IBOutlet weak var lengthLabel: UILabel!
    @IBOutlet weak var quantityLabel: UILabel!
    @IBOutlet weak var gaugeLabel: UILabel!
    
    // picker variables
    @IBOutlet weak var gaugePicker: UIPickerView!
    
    // on view did load function
        override func viewDidLoad() {
            super.viewDidLoad()
            
            print("in coil run view")
    //        initializeCoreData()
    //        // by default the button does not appear must add in code!!!!
    //        //------------------------------------------------------------
    //        // add an edit button, which is handled by the table view editing forRowAt
    //        self.navigationItem.leftBarButtonItem = self.editButtonItem
    //        // place an add button on the right side of the nav bar for adding a student
    //        // call addStudent function when clicked.
    //        let addButton = UIBarButtonItem(barButtonSystemItem: UIBarButtonItem.SystemItem.add, target: self, action: #selector(CoilTableViewController.addCoil))
    //        self.navigationItem.rightBarButtonItem = addButton
    //
    //        // obtain the values from the model
    //        self.updateModel()
    //
    //
    //        self.title = "Place List"
           
            
        }
    
    // MARK: -- UIPickerviewDataSource method
        func numberOfComponents(in pickerView: UIPickerView) -> Int {
            return 1
}
 // UIPickerviewDataSource method
        func pickerView(_ pickerView: UIPickerView, numberOfRowsInComponent component: Int) -> Int {
            return 1
}

    
    
   
    
    
    
    
}
