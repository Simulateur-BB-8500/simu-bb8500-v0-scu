# Description

The **Simulator Control Unit** (SCU) is the central processor of the system. This is the master unit of the simulator which handles the following functions:

* **Read the dashboard inputs** (switchs and levers activated by the train driver).
* **Control the dashboard outputs** (displays, gauges, light indicators, etc.).
* Implement the **simulation algorithms** to recreate the real locomotive behaviour.
* **Send the commands to the SGDU** when a dashboard action requires a soundtrack and/or needs to be transmitted to the game.
* **Receive and process the game data sent by the SGDU**, such as the train speed and the speed limit.

# Hardware

The V0 project was based on 2 **Arduino Due** boards (DUE1 and DUE2).

Excepts for the basic inputs which were directly connected to the MCU, most of the dashboard modules were detected or controlled through a dedicated circuit: in the V0 version of the simulator, there were **32 through-hole PCBs making the interface between the dashboard and the MCU** (power drivers, logic adapters, etc.).

# Embedded software

## Environment

The embedded software was developed in C++ under **Atmel Studio** v7.0.

## Structure

The project was organized as follow:

* `SCU-DUE1` : drivers and sketch of the **Arduino Due 1**.
* `SCU-DUE2` : drivers and sketch of the **Arduino Due 2**.
* `NTIU` : firmware of the **Needle Tuning Interface Unit** (PCB 36).
* `root` : **common drivers**.
