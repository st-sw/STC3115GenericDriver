# STC3115GenericDriver
STC3115 fuel gauge Open source generic driver

Hardware:
----------------
Can be used on any platform with I2C Master (pin SCL & SDA) connected to I2C Slave of STC3115 device.  <br />
For instance: STM32 Nucleo board, STM32 discovery board, Arduino, ...  <br />

The STC3115 is designed to be power supplied directly from the battery. In this case, the STC3115 remains active even if the whole platform is in standby or powered off.


SW Requirements:
----------------
Implement the I2C driver dependant on your platform.

SW Configuration:
----------------
Update the configuration file depending on the battery characteristics (Capacity, Internal Impedance, battery default OCV curve, ...), and the schematic (Resistor value used for current sensing)

SW Use:
----------------
The host driver access the STC3115 via I2C every 5s typically (or longer, up to 30s).  <br />
So a 5s timer is needed to implement.  <br />
It is not needed to access the STC3115 more often because the Battery charging/discharging variation is very slow.  <br />
However, even if the driver is access every 1s, the STC3115 algorithm still work properly.  <br />

Battery State of Charge:
----------------
The STC3115 driver use the ST OptimGauge(tm) algorithm to give the Optimum accuracy regarding the estimation of the battery state of charge (in %).

