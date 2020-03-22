//
//  HomeViewController.swift
//  CoilWind
//
//  ------------------------------------------------------------------------------
//  View for the home screen. the storyboard uses segues to go between other views
//
//  ------------------------------------------------------------------------------
//  Created by Zane Guess on 2/21/20.
//  Copyright © 2020 Capstone Team 15. All rights reserved.
//  @version 1.0

import UIKit
import Foundation
import CoreBluetooth

class HomeViewController: UIViewController {
    
    var ble : BlueToothModel!

    // view did load function is all that is needed
    @IBOutlet weak var connectedLabel: UILabel!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        print("loaded home page")
        
        if(connectedLabel.text == "Device Connected" || connectedLabel.text == "Device already connected"){
            connectDeviceOutlet.isEnabled = false
            disconnectButtonOutlet.isEnabled = true
        }
        else{
            connectDeviceOutlet.isEnabled = true
            disconnectButtonOutlet.isEnabled = false
        }
        ble = BlueToothModel()
    }
    
    @IBOutlet weak var connectDeviceOutlet: UIButton!
    @IBAction func ConnectDevice(_ sender: Any) {
        
        if(connectedLabel.text == "Device Connected"){
            return connectedLabel.text = "Device already connected"
        }
        connectedLabel.text = "Searching for device"
        
        ble.startUpCentralManager()
        connectDeviceOutlet.isEnabled = false
        disconnectButtonOutlet.isEnabled = true
    }
    
    
    @IBOutlet weak var disconnectButtonOutlet: UIButton!
    @IBAction func disconnectDevice(_ sender: Any) {
        
        ble.disconnectDevice()
        connectDeviceOutlet.isEnabled = true
        disconnectButtonOutlet.isEnabled = false
        print("device disconnected")
    }
    
    
    
}

