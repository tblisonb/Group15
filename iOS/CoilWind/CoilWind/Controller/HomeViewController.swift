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
    
    // corebluetooth module
    var ble = BlueToothModel()

  
    @IBOutlet weak var connectedLabel: UILabel!
    
    //view did load
    override func viewDidLoad() {
        super.viewDidLoad()
        print("loaded home page")
        
        // if device is already connected on load disable connect button and enable disconnect button
        if(connectedLabel.text == "Device connected" || connectedLabel.text == "Device already connected"){
            connectDeviceOutlet.isEnabled = false
            disconnectButtonOutlet.isEnabled = true
        }
            // if on load no device is connected enable connect button and disable disconnect button
        else{
            connectDeviceOutlet.isEnabled = true
            disconnectButtonOutlet.isEnabled = false
        }
        

    }
    
    // connect button runs the connect methods in the bluetoothmodel class. while disabling and activating the proper buttons
    @IBOutlet weak var connectDeviceOutlet: UIButton!
    @IBAction func ConnectDevice(_ sender: Any) {
        
        if(connectedLabel.text == "Device connected"){
            return connectedLabel.text = "Device already connected"
        }
        connectedLabel.text = "Searching for device"
        
        print("calling ble module to connect")
        ble.startUpCentralManager()
        print("back in home screen device")
        connectDeviceOutlet.isEnabled = false
        disconnectButtonOutlet.isEnabled = true
    }
    
    
    // disconnect button runs the disconnect methods in the bluetoothmodel class. while disabling and activating the proper buttons
    @IBOutlet weak var disconnectButtonOutlet: UIButton!
    @IBAction func disconnectDevice(_ sender: Any) {
        
        print("calling bluetooth modular to disconnect")
        ble.disconnectDevice()
        connectDeviceOutlet.isEnabled = true
        disconnectButtonOutlet.isEnabled = false
        print("device disconnected")
    }
    
    
    
}

