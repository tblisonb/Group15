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
private struct BLEIDs{

    // these are dummy ids so the sake of testing other code areas. once the offical ids are known from the
    // machine we will change
    static let coilServiceUUID = CBUUID(string: "49535343-FE7D-4AE5-8FA9-9FAFD205E455")
    static let coilCharactersticUUID = CBUUID(string:"49535343-1E4D-4BD9-BA61-23C647249616")
    static let blockingUUID = CBUUID(string:"49535343-8841-43F4-A8D4-ECBE34729BB3")
//49535343-8841-43F4-A8D4-ECBE34729BB3
}

// class to allow all the bluetooth functionality throughout application
public class BlueToothModel: NSObject, CBCentralManagerDelegate, CBPeripheralDelegate{
    
    var Home: HomeViewController!
    var quickRun: QuickRunViewController!
    var coilRun: CoilRunViewController!

    private var centralManager : CBCentralManager!
    private var ATmega3208Board : CBPeripheral?
    private var coilService : CBService!
    private var coilCharacteristic : CBCharacteristic!
    private var activeCharacteristic : CBCharacteristic!



    //MARK: - Functions to start the central manager
    //*****************************************
    func startUpCentralManager() {

        centralManager = CBCentralManager(delegate: self, queue: nil)
        
    }

    public func centralManagerDidUpdateState(_ central: CBCentralManager) {

        switch (central.state) {

        case .poweredOff: central.stopScan()
        case .poweredOn:print("ble is on")
              print("Starting scan")
              centralManager?.scanForPeripherals(
                withServices: [BLEIDs.coilServiceUUID], options: [
                      CBCentralManagerScanOptionAllowDuplicatesKey : NSNumber(value: true as Bool)
                  ]
              )
        case .resetting: break
        case .unauthorized: break
        case .unknown:break
        

        case .unsupported:break
            
        @unknown default:
            fatalError("unknown state")
        }
    }
    
    // end functions to start the central manager
    //*****************************************


    // MARK: - Functions to discover ble devices
    //*****************************************
//    func discoverDevice() {
//
//        print("Starting scan")
//        centralManager?.scanForPeripherals(withServices: [BLEIDs.coilServiceUUID], options: [CBCentralManagerScanOptionAllowDuplicatesKey:false])
//    }

    public func centralManager(_ central: CBCentralManager, didDiscover peripheral: CBPeripheral, advertisementData: [String : Any], rssi RSSI: NSNumber){
        
        if ATmega3208Board == nil {

            print("Found a new Periphal advertising wire cutting service")
            ATmega3208Board = peripheral
            
            centralManager?.connect(peripheral, options: nil)

           
        }
    }
    


    // end functions to discover BLE devices
    //*****************************************

    // MARK: - Functions to connect to a device
    //*****************************************


    // a device connection is complete
    public func centralManager(_ central: CBCentralManager, didConnect peripheral: CBPeripheral) {

        print("Connection complete \(ATmega3208Board!) \(peripheral)")
        peripheral.delegate = self
        centralManager.stopScan()

        Home.connectedLabel.text = "Device connected"
        peripheral.discoverServices([BLEIDs.coilServiceUUID])

    }

    // end functions to connect to BLE device
    //*****************************************




    // MARK: - Functions to discover the services on a device
     //*****************************************
 

    public func peripheral(_ peripheral: CBPeripheral, didDiscoverServices error: Error?) {
        print("discovered services")

        for service in peripheral.services! {

            print("Found service \(service)")

            if service.uuid == BLEIDs.coilServiceUUID {
                coilService = service
                peripheral.discoverCharacteristics([BLEIDs.coilCharactersticUUID], for: service)

            }
        }


    }
    // end functions to connect to BLE device
    //*****************************************




    // MARK: - Functions to discover the characteristics
    //*****************************************

    public func peripheral(_ peripheral: CBPeripheral, didDiscoverCharacteristicsFor service: CBService, error: Error?) {

        for characteristic in service.characteristics!{

            print("Found characteristic \(characteristic)")

            switch characteristic.uuid {
            case BLEIDs.coilCharactersticUUID:  coilCharacteristic = characteristic
            case BLEIDs.blockingUUID: activeCharacteristic = characteristic
            default: break

        }
        }
    }
    

    // end functions to connect to BLE device
    //*****************************************
    
    func writeCoilCharacteristic(data: Data)
    {
        let ns = NSData(data: data)
        ATmega3208Board!.writeValue(ns as Data, for: coilCharacteristic, type: CBCharacteristicWriteType.withResponse)
        print("write complete")
        
    }
    
    // MARK: - Functions to handle disconnection
    //*****************************************
    func disconnectDevice(){

        centralManager.cancelPeripheralConnection(ATmega3208Board!)
    }

    // disconnected a device
    private func centralManager(central: CBCentralManager, didDisconnectPeripheral peripheral: CBPeripheral, error: NSError?) {

        print("Disconnected \(peripheral)")
        ATmega3208Board = nil
        Home.connectedLabel.text = "Device disconnected"

    }
    // end functions to disconnect to BLE device
    //*****************************************
    
    // possible set up for strings
//         let string = "hello"
//
//
//         let bytes: [UInt8] = Array(string.utf8)
//
//
//         let data = NSData(bytes: bytes, length: bytes.count)
//
//
//         capsenseLedBoard!.writeValue(data, forCharacteristic: ledCharacteristic, type: CBCharacteristicWriteType.WithResponse)
    
    //*************************************************************************************************************************
    //the below methods are for later version after main functionality has been established
    // the below code will help to prevent errors and system crashes from user repeatedly hitting the run device button
    //*************************************************************************************************************************
    
//  MARK: -functions to have the coil cutting device update a value of the app so that the run device button can be toggled off while
//  wire cutter is active
//
    func writeActiveNotify(state: Bool)
    {
        ATmega3208Board!.setNotifyValue(state, for: activeCharacteristic)
    }

    var activeValue = 0

    // This delegate function is called when an updated value is received from the Bluetooth Stack
       //if a 1 is received the function will toggle button as inactive
    private func peripheral(peripheral: CBPeripheral, didUpdateValueForCharacteristic characteristic: CBCharacteristic, error: NSError?) {
        if characteristic == activeCharacteristic {
            let out: NSInteger = 0
            activeValue = out

        }
    }

}
