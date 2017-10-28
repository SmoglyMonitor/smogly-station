# Smogly Station
Formerly EnviroMonitorStation (part of Smogly project) is an ESP8266 based, outdoor environmental monitoring station. It includes temperature, humidity and most importantly, PM2.5, PM10 dust monitoring.

Features:
- PM1.0, PM2.5, PM10 monitoring
- temperature, humidit
- post data to custom backend
- WiFi auto configuration
- 12V/5V powered

Currently Smogly station is DIY project, we don't provide ability to buy monitoring station, you need to build it yourself.
We also designed [PCB](https://github.com/EnviroMonitor/EnviroMonitorElectronics) and [enclosure](https://github.com/EnviroMonitor/EnviroMonitorEnclosure) so you can easily build your own sensor. Moreover - every piece of the project is Open Source, so you can modify it for your needs.

Please stay tuned, this is work in progress. Prototypes are being tested and we will post usable software and HW design soon.

# Hardware

## Bill of Materials
Below is the list of parts you will need to build monitoring station:

- Wemos D1 mini ESP8266 based development board (example: https://goo.gl/nk0Xvn)
- PMS3003 - Plantower particulate matter sensor detecting PM1.0, PM2.5, PM10 (example: https://goo.gl/ZB6P51)
- Si7021 temperature and humidity sensors (example: https://goo.gl/RCU0Vk)
- DC-DC step down power supply module, preferably based on LM2596 (example: https://goo.gl/TbNs1Y)
- AC power supply with 12V DC 1A output (example: https://goo.gl/fVu5LT)
- N-MOSFET, example: AUIRLZ44Z
- 2.54 pitch male pin headers: 2 x 8 pins (Wemos connectors, usually included with Wemos), 1 x 6 pins (PMS3003 connector), 3 x 3 pins (DS and HEAT DC switch), 1 x 4 pins (I2C bus)
- 2.54 ptich female pin headers: 2 x 8 pins for wemos socket, 1 x 6 pin (to solder instead of original PMS3003 plug)
- 3 x 3.5 mm pitch 2 pin screw terminals
- resistors: 1 x 4.7 kΩ, 1 x 47 kΩ, 1 x 1 kΩ
- [PCB](https://github.com/EnviroMonitor/EnviroMonitorElectronics)
- [enclosure](https://github.com/EnviroMonitor/EnviroMonitorEnclosure)


# Software
## Backend configuration
Before sensor is added to the system, it needs to be registered on the backend side. After registration you will receive couple of parameters:
- API key - to be able to post and receive data from backend

## Sensor configuration
After sensor is connected to power, it start local AccessPoint for initial configuration. User needs to connect to this AccessPoint and as a next step, familiar HotSpot configuration page should be presented. Using this simple page user can configure:
- API access key (generated during sensor registration)
- WiFi network and password to use for sending data
- backend server address

Once you finish configuration, sensor will reboot, and join configured WiFi network. If there was any error, e.g. wrong password, sensor will again reboot into AccessPoint mode, so you are able to correct configuration.

## How we measure parameters
In every cycle device measures couple of parameters and sends them to EnviroMonitorWe backend. In current version of hardware we measure:
- PM2.5 and PM10
- external temperature and humidity

# Development
Smogly project is developed as a community and open source / open hardware project. We use Github for all the development workflow.
Smogly Station is Arduino based project, but we use [PlatformIO](http://platformio.org/) development environment. Please follow PlatformIO [getting started guide](http://platformio.org/get-started) to set up your environment. We try too keep our code Arduino compatible, so it's possible to use Arduino IDE for development, but we strongly recommend using PlatformIO.
