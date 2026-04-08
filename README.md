# vallox-
Remote control system for Vallox ventilation machine​

Introduction 

This IoT project is developed by Valtteri Pikkarainen, Alex Toro, and Tahereh Yousefi, focuses on creating a remote-control system for the Vallox Digit SE ventilation machine. By integrating Internet of Things (IoT) technology, the system enables devices to connect to the internet to share data and be remote controlled. 
The project involves building a communication bridge between the Vallox unit and a user interface. The system reads data from the Vallox Digit SE using an RS485 connection. This data is processed through an RS485 to TTL converter and an ESP-01 Wi-Fi module, which then transmits the information via an MQTT Broker to Home Assistant. This allows the user to monitor and control the ventilation unit through a phone or PC. 

Problem Statement
Older ventilation units like the Vallox Digit SE lack native internet connectivity, meaning they cannot participate in a modern smart home ecosystem. Without this connection, users cannot easily monitor performance remotely or integrate the device into automated energy-saving routines. 

Objectives 
Establish Connectivity: Connect the Vallox hardware to the internet. 
Data Integration: Enable the system to share and use data effectively. 
Accessibility: Provide a user-friendly interface via Home Assistant for remote management. 

Motivation
Our team is highly motivated to bridge the gap between traditional mechanical systems and modern smart home technology. We are driven by the challenge of using affordable components like the ESP-01 to transform a standalone unit into an integrated IoT device.
