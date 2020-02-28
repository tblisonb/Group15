//
//  BlueToothModel.swift
//  CoilWind
//  ----------------------------------------------------------------
//  The Core Bluetooth framework to get the bluetooth to work with
//  The atmega 3208 board as well as others. Allowing for the control of the
//  wire cutting device from the iphone
//  ----------------------------------------------------------------
//  @version 1.0
//  Created by Zane Guess on 2/27/20.
//  Copyright © 2020 Capstone Team 15. All rights reserved.


import Foundation
import CoreBluetooth

 // service and characteristic ids so that the bluetooth connection can interact
private struct BLEIDs{
    
    // these are dummy ids so the sake of testing other code areas. once the offical ids are known from the
    // machine we will change
    // ********************* UPDATE UUID WHEN KNOWN **************************************
    static let coilServiceUUID = CBUUID(string: "00000000-0000-1000-8000-00805F9B34F0")
    static let coilCharactersticUUID = CBUUID(string:"00000000-0000-1000-8000-00805F9B34F1")
    
}

// class to allow all the bluetooth functionality throughout application
public class BlueToothModel: NSObject, CBCentralManagerDelegate, CBPeripheralDelegate{
    
    private var centralManager : CBCentralManager!
    private var ATmega3208Board : CBPeripheral?
    private var coilService : CBService!
    private var coilCharacteristic : CBCharacteristic!
    
    public func centralManagerDidUpdateState(_ central: CBCentralManager) {
        switch (central.state) {
        case .poweredOff: break
        case .poweredOn:
            //NotificationCenter.defaultCenter().postNotificationName(RCNotifications.BluetoothReady, object: nil)
            print("Bluetooth is on")
        case .resetting: break
        case .unauthorized: break
        case .unknown:break
        case .unsupported:break
        @unknown default:
            <#fatalError()#>
        }
    }
    
   

    
    
    
}
