# OpenPAYGO Token v2 - Hardware Examples Repository

This project is supported by the EnAccess Foundation (https://enaccess.org/)


## Content

### Neutral C Implentation of OPAYGO

This implementation is meant to be easy to port to other devices. 
It also includes a "unix_device" folder that shows an example of the implementation for the Unix platform as a CLI tool. 
To port it to another device, simply implement the functions found in that UNIX example (BlinkRedLED, GetPressedKey, etc.) for your target system and replace the import. 

### Arduino Firmware Implementation
 
This implementation with 3 different input modes (IR Remote, Membrane Keypad, USB Keypad) and supports factory setup via UART. 

A small tool is also provided for the factory setup. 

### Tutorial on how to add to a simple product

These tutorials are based on the Arduino firmware implementation show how to wire a full product. 


## Documentation

**See the main repository of the project here for the full documentation:** https://github.com/EnAccess/OpenPAYGO


## NOTE 
If you have pulled or downloaded this implementation before the official OpenPAYGO Token release on the 10th of October 2019, 
please make sure to update to the latest version before using in production. 


## Changelog

2020-11-13: v2.1.2 release
- Fixes issue with unordered token entry in example implementation

2020-10-23: v2.1.1 release
- Improved factory setup for Arduino example (compatible with the factory setup tools of the other repository)
- Improved general structure of Arduino project

2020-09-17: v2.1.0 release
- Updated the examples to add the unordered token entry feature that was introduced with v2.1 on 2019-11-15 as part of the main repository 
- Fixed compatibility with OSX for the Neutral C Implementation
- Included Makefile in the Neutral C Implementation for ease of use (thanks @martinjaeger)
- Fixed issue in Arduino example were token type was not properly taken into account

2019-09-09: v2.0.0 release
- Updated example Arduino code documentation
- Fixed a bug in the neutral device example implementation that would prevent the value of the counter to be stored immediately after a counter sync call. 
- Changed the min. Token jump to match the value recommended in the documentation.
- Small refactor for clarity in the Arduino implementation

2019-09-24: v2.0.0 rc2
- Added the first verison of the Arduino implementation

2019-09-18: v2.0.0 rc1
- Added extended token example implementation

2019-08-29: v2.0.0 beta
- Fully functional version with all core v2.0 features

2019-06-29: v2.0.0 alpha
- First functional pre-release version
