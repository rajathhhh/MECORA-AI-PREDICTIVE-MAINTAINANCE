# MECORA-AI-PREDICTIVE-MAINTAINANCE
ESP32-based AI predictive maintenance prototype system that uses vibration and temperature data to identify abnormal operating conditions.

1. Overview

Mecora is a low-cost machine monitoring system designed to detect unusual motor behaviour before it develops into a potential mechanical failure.

The system collects real-time vibration and temperature readings, learns normal operating behaviour, and identifies deviations using an anomaly-scoring approach.

2. Problem Statement

Unexpected machine failures can lead to equipment damage, production downtime, and increased maintenance costs.

Mecora aims to provide an affordable monitoring solution that can identify abnormal operating patterns and support early fault detection.

3. Hardware Components

Component	Purpose
ESP32	Main processing and control unit
MPU9250	Vibration and motion sensing
DS18B20	Temperature monitoring
L298N	Motor control
DC Motor	Test machine

4. System Architecture

1. Data Acquisition: Collect vibration and temperature readings from sensors.
2. Baseline Learning: Establish normal operating behaviour.
3. Anomaly Detection: Calculate deviations from the learned baseline.
4. Fault Handling: Identify sustained abnormal conditions.
5. Motor Protection: Trigger automatic motor shutdown when sustained fault conditions are detected.

5. Technologies Used

* Embedded C/C++
* ESP32
* Arduino IDE
* MPU9250 (I2C)
* DS18B20 (OneWire)
* Sensor interfacing
* Motor control
* Anomaly detection

6. Current Development Status

Mecora is an ongoing hardware prototype.

Current development focuses on sensor integration, baseline learning, vibration analysis, anomaly detection, and automatic motor protection.

7. Future Scope

* Machine learning-based fault classification.
* Real-time monitoring dashboard.
* Wireless machine-health monitoring.
* Predictive maintenance across different motor types.
* Historical data analysis and failure prediction.

8. Project Information

Project: Mecora — AI-Based Predictive Maintenance System

Developer: Rajath R.

Field: Electronics and Communication Engineering

Status: Ongoing

⸻

Developed as a low-cost approach towards intelligent machine health monitoring and predictive maintenance.
