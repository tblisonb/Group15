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
    
    
    //MARK: - Functions to start the central manager
    //*****************************************
    func startUpCentralManager() {
        
        centralManager = CBCentralManager(delegate: self, queue: nil)
    }
    
    public func centralManagerDidUpdateState(_ central: CBCentralManager) {
        
        switch (central.state) {
            
        case .poweredOff: break
        case .poweredOn:
            print("Bluetooth is on")
        case .resetting: break
        case .unauthorized: break
        case .unknown:break
        case .unsupported:break
        @unknown default:
            <#fatalError()#>
        }
    }
    // end functions to start the central manager
    //*****************************************
   
    
    // MARK: - Functions to discover ble devices
    //*****************************************
    func discoverDevice() {
        
        print("Starting scan")
        centralManager.scanForPeripherals(withServices: [BLEIDs.coilServiceUUID], options: [CBCentralManagerScanOptionAllowDuplicatesKey:false])
    }
    
    private func centralManager(central: CBCentralManager, didDiscoverPeripheral peripheral: CBPeripheral, advertisementData: [String : AnyObject], RSSI: NSNumber){
        
        if ATmega3208Board == nil {
            
            print("Found a new Periphal advertising wire cutting service")
            
            ATmega3208Board = peripheral
            centralManager.stopScan()
        }
    }

    // end functions to discover BLE devices
    //*****************************************
    
    // MARK: - Functions to connect to a device
    //*****************************************
    func connectToDevice(){
        
        centralManager.connect(ATmega3208Board!, options: nil)
    }
    
    // a device connection is complete
    func centralManager(central: CBCentralManager, didConnectPeripheral peripheral: CBPeripheral) {
        
        print("Connection complete \(ATmega3208Board!) \(peripheral)")
        ATmega3208Board!.delegate = self
    }
    
    // end functions to connect to BLE device
    //*****************************************
    
    // MARK: - Functions to handle disconnection
    //*****************************************
    func disconnectDevice(){
        
        centralManager.cancelPeripheralConnection(ATmega3208Board!)
    }
    
    // disconnected a device
    private func centralManager(central: CBCentralManager, didDisconnectPeripheral peripheral: CBPeripheral, error: NSError?) {
        
        print("Disconnected \(peripheral)")
        ATmega3208Board = nil
    }
    // end functions to disconnect to BLE device
    //*****************************************
    
    
    // MARK: - Functions to discover the services on a device
     //*****************************************
    func discoverServices(){
        
        ATmega3208Board!.discoverServices(nil)
    }
    
    private func peripheral(peripheral: CBPeripheral, didDiscoverServices error: NSError?) {
        print("discovered services")
        
        for service in peripheral.services! {
            
            print("Found service \(service)")
            
            if service.uuid == BLEIDs.coilServiceUUID {
                coilService = service
            }
        }
        
    }
    // end functions to connect to BLE device
    //*****************************************
    
    
    
    
    // MARK: - Functions to discover the characteristics
    //*****************************************
    func discoverCharacteristics(){
        
        ATmega3208Board!.discoverCharacteristics(nil, for: coilService)
    }
    
    private func peripheral(peripheral: CBPeripheral, didDiscoverCharacteristicsForService service: CBService, error: NSError?) {
        
        for characteristic in service.characteristics!{
            
            print("Found characteristic \(characteristic)")
            
            if characteristic.uuid == BLEIDs.coilCharactersticUUID{
                coilCharacteristic = characteristic
            }
            
        }
        
    }
    
    // end functions to connect to BLE device
    //*****************************************
    
}
