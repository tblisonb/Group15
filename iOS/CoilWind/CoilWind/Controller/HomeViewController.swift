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

extension Notification.Name{
    static let ConnectionComplete = Notification.Name("connectioncomplete")
    static let disconnectionComplete = Notification.Name("disconnectioncomplete")
    
}

class HomeViewController: UIViewController {
    
    // corebluetooth module
    var ble : BlueToothModel!
    var deviceName : String = ""
  
    @IBOutlet weak var connectedLabel: UILabel!
    
    //view did load
    override func viewDidLoad() {
        super.viewDidLoad()
        print("loaded home page")
        
        ble = BlueToothModel()
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
        
//
        NotificationCenter.default.addObserver(self, selector: #selector(connectionComplete), name: Notification.Name("ConnectionComplete"), object: nil)
//
        NotificationCenter.default.addObserver(self, selector: #selector(deviceDisconnected), name: Notification.Name("disconnectionComplete"), object: nil)

//        NotificationCenter.default.addObserver(forName: NSNotification.Name(rawValue: notifications.disconnectionComplete), object: nil, queue: OperationQueue.main) { _ in self.deviceDisconnected()}
        
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

        connectDeviceOutlet.isEnabled = false
        disconnectButtonOutlet.isEnabled = true

    }
    
    


    // disconnect button runs the disconnect methods in the bluetoothmodel class. while disabling and activating the proper buttons
//
    
    @IBOutlet weak var disconnectButtonOutlet: UIButton!
    @IBAction func disconnectDevice(_ sender: Any) {

        print("calling bluetooth modular to disconnect")
        ble.disconnectDevice()
        connectDeviceOutlet.isEnabled = true
        disconnectButtonOutlet.isEnabled = false

        print("device disconnected")
    }
    
    

    
    
// update label on connection
    @objc func connectionComplete(notification: NSNotification){
        print(ble.deviceName)
        connectedLabel.text = "Device Connected \(ble.deviceName)"
        print(connectedLabel.text!)
    }
    
    //update label on disconnect
    @objc func deviceDisconnected(notification: NSNotification){
        connectedLabel.text = "\(ble.deviceName) disconnected"
    }
    
    // MARK: - Navigation
    // Storyboard seque: do any advance work before navigation, and/or pass data
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        super.prepare(for: segue, sender: sender)
        
        // prepping the the segue to include the relative data to be passed
        if segue.identifier == "QuickRunSegue" {
            let quickviewController:QuickRunViewController = segue.destination as! QuickRunViewController
            quickviewController.ble = self.ble

        }
        if segue.identifier == "TableViewSegue" {
            let tableviewController:CoilTableViewController = segue.destination as! CoilTableViewController
            tableviewController.ble = self.ble
    }

    
}
}

