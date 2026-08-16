package com.example.vhalcanbridge

import android.app.Activity
import android.os.Bundle
import android.util.Log
import android.car.Car
import android.car.hardware.property.CarPropertyManager

class MainActivity : Activity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        // TODO(aaos15): validate exact permission and lifecycle handling for your product setup.
        val car = Car.createCar(this)
        val propertyManager = car.getCarManager(Car.PROPERTY_SERVICE) as CarPropertyManager

        // TODO(aaos15): replace with generated VehicleProperty constant usage in final integration.
        val perfVehicleSpeedPropertyId = 0x11600207
        Log.i("VhalCanBridgeClient", "CarPropertyManager ready for property=$perfVehicleSpeedPropertyId via $propertyManager")
    }
}
