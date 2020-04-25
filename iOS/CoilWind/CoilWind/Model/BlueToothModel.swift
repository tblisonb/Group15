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

// // service and characteristic ids so that the bluetooth connection can interact
//49535343-FE7D-4AE5-8FA9-9FAFD205E455


// class to allow all the bluetooth functionality throughout application
 class BlueToothModel: NSObject, CBCentralManagerDelegate, CBPeripheralDelegate{
    
    var Home = HomeViewController()
    var quickRun: QuickRunViewController!
    var coilRun: CoilRunViewController!
    var peripherals: [CBPeripheral] = []
    var deviceName: String = ""
    var coilServiceUUID = CBUUID.init(string:  "49535343-FE7D-4AE5-8FA9-9FAFD205E455")
    var coilCharactersticUUID = CBUUID.init(string:"49535343-1E4D-4BD9-BA61-23C647249616")
    var blockingUUID = CBUUID(string:"49535343-8841-43F4-A8D4-ECBE34729BB3")

    var centralManager : CBCentralManager!
    var ATmega3208Board : CBPeripheral?
    var coilService : CBService!
    var coilCharacteristic : CBCharacteristic!
    var activeCharacteristic : CBCharacteristic!



    //MARK: - Functions to start the central manager
    //*****************************************
    func startUpCentralManager() {

        centralManager = CBCentralManager(delegate: self, queue: nil)
        
    }

    func centralManagerDidUpdateState(_ central: CBCentralManager) {

        if central.state == CBManagerState.poweredOn{
            print("ble is on")
            print("Starting scan")
            centralManager?.scanForPeripherals(withServices: nil, options: [CBCentralManagerScanOptionAllowDuplicatesKey : false])
            print("scanning")

        }
        else{
            centralManager?.stopScan()
        }
//[coilServiceUUID]

    }
    /*We also need to stop scanning created a function that calls "stopScan"*/
     func cancelScan() {
         self.centralManager?.stopScan()
         print("Scan Stopped")
         print("Number of Peripherals Found: \(peripherals.count)")
     }
    
    // end functions to start the central manager
    //*****************************************


    // MARK: - Functions to discover ble devices
    //*****************************************
    // gets called when the ble device with the services is found
     func centralManager(_ central: CBCentralManager, didDiscover peripheral: CBPeripheral, advertisementData: [String : Any], rssi RSSI: NSNumber){
       // print(advertisementData)
        print(advertisementData)
        if peripheral.name == "AVR-BLE_9ABD" {
        if ATmega3208Board == nil {

            print("Found a new Periphal advertising wire cutting service")
            
            ATmega3208Board = peripheral

            centralManager?.connect(peripheral, options: nil)
            centralManager.stopScan()

            }}
    }
    


    // end functions to discover BLE devices
    //*****************************************

    
    func centralManager(_ central: CBCentralManager, didFailToConnect peripheral: CBPeripheral, error: Error?) {
        if error != nil {
            print("Failed to connect to peripheral")
            return
        }
    }
    
    // MARK: - Functions to connect to a device
    //*****************************************


    // a device connection is complete
    func centralManager(_ central: CBCentralManager, didConnect peripheral: CBPeripheral) {

        print("Connection complete \(ATmega3208Board!) \(peripheral)")
        deviceName = peripheral.name!
        peripheral.delegate = self


        NotificationCenter.default.post(name: Notification.Name("ConnectionComplete"), object: nil)

   
        peripheral.discoverServices([coilServiceUUID])

    }

    // end functions to connect to BLE device
    //*****************************************




    // MARK: - Functions to discover the services on a device
     //*****************************************
 

     func peripheral(_ peripheral: CBPeripheral, didDiscoverServices error: Error?) {
        print("discovered services")
        print(peripheral.services!)

        for service in peripheral.services! {

            print("Found service \(service)")

            if service.uuid == coilServiceUUID {
                coilService = service
                peripheral.discoverCharacteristics([coilCharactersticUUID], for: service)

            }
        }


    }
    // end functions to connect to BLE device
    //*****************************************




    // MARK: - Functions to discover the characteristics
    //*****************************************

     func peripheral(_ peripheral: CBPeripheral, didDiscoverCharacteristicsFor service: CBService, error: Error?) {

        for characteristic in service.characteristics!{

            print("Found characteristic \(characteristic)")

            switch characteristic.uuid {
            case coilCharactersticUUID:  coilCharacteristic = characteristic
            case blockingUUID: activeCharacteristic = characteristic
            default: break

        }
        }
    }
    

    // end functions to connect to BLE device
    //*****************************************
    
    func writeCoilCharacteristic(data: Data){
        let ns = NSData(data: data)
        print(peripherals);
        ATmega3208Board!.writeValue(ns as Data, for: coilCharacteristic, type: CBCharacteristicWriteType.withResponse)
        print(ns)
        print("write complete")
        
    }
    
    // MARK: - Functions to handle disconnection
    //*****************************************
    func disconnectDevice(){
        print("in disconnect")
        centralManager?.cancelPeripheralConnection(ATmega3208Board!)
        centralManager?.stopScan()
    }

    // disconnected a device
    func centralManager(_ central: CBCentralManager, didDisconnectPeripheral peripheral: CBPeripheral, error: Error?) {

        print("Disconnected \(peripheral)")
        NotificationCenter.default.post(name: Notification.Name("disconnectionComplete"), object: nil)
        ATmega3208Board = nil
        deviceName = ""

    }
    // end functions to disconnect to BLE device
    //*****************************************
     //*************************************************************************************************************************
    //the below methods are for later version after main functionality has been established
    // the below code will help to prevent errors and system crashes from user repeatedly hitting the run device button
    //*************************************************************************************************************************
    
//  MARK: -functions to have the coil cutting device update a value of the app so that the run device button can be toggled off while
//  wire cutter is active
//
//    func writeActiveNotify(state: Bool)
//    {
//        ATmega3208Board!.setNotifyValue(state, for: activeCharacteristic)
//    }
//
//    var activeValue = 0
//
//    // This delegate function is called when an updated value is received from the Bluetooth Stack
//       //if a 1 is received the function will toggle button as inactive
//    private func peripheral(peripheral: CBPeripheral, didUpdateValueForCharacteristic characteristic: CBCharacteristic, error: NSError?) {
//        if characteristic == activeCharacteristic {
//            let out: NSInteger = 0
//            activeValue = out
//
//        }
//    }

}
