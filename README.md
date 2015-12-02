# STC3115GenericDriver
STC3115 fuel gauge Open source generic driver

Hardware:
----------------
Can be use on any platform with I2C Master (pin SCL & SDA) connected to STC3115 I2C Slave.  <br />
For instance: STM32 Nucleo board, STM32 discovery board, Arduino, ... 

SW Requirements:
----------------
Implement the I2C driver dependant on your platform.

SW Use:
----------------
The host driver access the STC3115 via I2C every 5s typically (or longer, up to 30s).  <br />
So a 5s timer is needed to implement.  <br />
It is not needed to access the STC3115 more often because the Battery charging/discharging variation is very slow.  <br />
However, even if the driver is access every 1s, the STC3115 algorithm still work properly.  <br />

Battery State of Charge:
----------------
The STC3115 drivers used the ST OptimGauge(tm) algorithm to give the Optimum accuracy regarding the estimation of the battery state of charge (in %).

