package com.example.vhaldemo

import android.app.Activity
import android.car.Car
import android.car.VehiclePropertyIds
import android.car.hardware.property.CarPropertyManager
import android.os.Bundle
import android.util.Log
import android.widget.TextView

class MainActivity : Activity() {
    private var car: Car? = null
    private var propertyManager: CarPropertyManager? = null
    private lateinit var speedText: TextView

    private val callback = object : CarPropertyManager.CarPropertyEventCallback {
        override fun onChangeEvent(value: android.car.hardware.CarPropertyValue<*>) {
            if (value.propertyId == VehiclePropertyIds.PERF_VEHICLE_SPEED) {
                val speed = value.value as? Float ?: return
                val text = "Speed: ${"%.2f".format(speed)} m/s"
                speedText.text = text
                Log.i("CanVhalDemoApp", text)
            }
        }

        override fun onErrorEvent(propId: Int, zone: Int) = Unit
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        speedText = findViewById(R.id.speedText)

        car = Car.createCar(this)
        propertyManager = car?.getCarManager(Car.PROPERTY_SERVICE) as? CarPropertyManager

        propertyManager?.registerCallback(
            callback,
            VehiclePropertyIds.PERF_VEHICLE_SPEED,
            CarPropertyManager.SENSOR_RATE_ONCHANGE,
        )
    }

    override fun onDestroy() {
        propertyManager?.unregisterCallback(callback)
        car?.disconnect()
        super.onDestroy()
    }
}
