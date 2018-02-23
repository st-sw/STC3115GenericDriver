# STC3115GenericDriver
STC3115 fuel gauge Open source generic driver
(STC3115 Generic Driver)

Device under test:
----------------
Device:       STC3115 Battery Gas gauge.  <br />
Manufacturer: STMicroelectronics <br />

Typical Application:  Monitor a single cell battery <br />
Package:      CSP and DFN10 (9 pins used) <br />
Operating supply: 2.7V to 4.5V  <br />


Hardware:
----------------
Can be used on any platform with I2C Master (SCL & SDA pins) connected to I2C Slave of STC3115 device.  <br />
For instance: STM32 Nucleo board, STM32 discovery board, Arduino, Raspberry Pi, Android dev kit, ...  <br />

The STC3115 is designed to be power supplied directly from the battery. In this case, the STC3115 remains active even if the whole platform is in standby or powered off.


SW Requirements:
----------------
Implement the I2C driver depending on your platform.

SW Configuration:
----------------
Update the configuration file depending on the battery characteristics (Capacity, Internal Impedance, battery default OCV curve, ...), and the schematic (Resistor value used for current sensing)

SW Use:
----------------
The host driver accesses the STC3115 registers via I2C every 5s typically (or longer, up to 30s).  <br />
So a 5s timer is required to be implemented.  <br />

The STC3115 monitors the battery continuously. <br />
But It is not needed for the host to access the STC3115 more often because the Battery charging/discharging variation is very slow.  <br />
However, even if the driver is accessed more frequently (every 1s), the STC3115 algorithm still works properly.  <br />

Battery State of Charge:
----------------
The STC3115 driver uses the ST OptimGauge(tm) algorithm to give the Optimum accuracy regarding the estimation of the battery state of charge (in %).

Notes:
----------------
Source code Examples are based on STSW-BAT001 package: STC3115 Open source driver.  

The core of source code in this repository is an updated and corrected version of the one provided on manufacturer website.

Issues:
----------------
For common issues, please refer to the FAQ first.

A short FAQ is available here: 
https://github.com/st-sw/STC3115GenericDriver/wiki/STC3115-FAQ
