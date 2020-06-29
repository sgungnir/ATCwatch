This is a fork of Aaron Christophel's excellent P8WATCH arduino firmware.

The original code has european (international) date format (day/month/year), and 24hr time, changed this to US format (easy to revert) but also added day of the week (removed year for space reasons).

The time is now in 12hr format with AM/PM indicator.

I plan to make the date and hour format change optional (have a compile option) but for now it is stuck in US format (easy to revert).

A new sideways navigation allows quick access to the main apps without removing the "app drawer" vertical navigation that has all the diagnositcs (as well as the main apps).

Sideways navigation Home, Notifications, Calendar(new), Heart Rate, Settings and Info screen (easy to change array defined in menu.cpp

I have added a Calendar app (very simple, will update style to match, more features come later) with a vertical navigation for the months (starts on current date, slide up for next month, down for previous month)

Icons now have alpha and I am slowly changing them to have rounded edges.

Standard header for all pages is the goal (just starting with this, only notify has it now) to include date/ time and small app icon on the top of every page.

General font and format changes are in progress to have every page in the same format.

## License:
Orignal license holds, see below...

ORIGINAL REPO INFO BELOW, VERY IMPORTANT FOR COMPILING AND ATTRIBUTION, THANKS AGAIN TO Aaron Christophel!!

-------------------------------------------------------------------------------------------------------------------------
# ATCwatch  -WatcH
Custom Arduino C++ firmware for the P8 and PineTime plus many more DaFit Smartwatches

About 150-200uA standby current consumtion.Currently 92 Hours Runtime with heavy notification and usage!.
Basic menu system and notification working.

If you want to use it on PineTime comment the #define P8WATCH to enable the PineTime Pinout. 
For other watches please try to check the pinout of them and change the pinout as needed.

#### You can support my work via paypal: https://paypal.me/hoverboard1 this keeps projects like this comming.

Use this portable Arduino version: https://atcnetz.de/downloads/D6Arduino.rar
here is a manual on how to use it: https://youtu.be/3gjmEdEDJ5A
Unzip, open Arduino.exe open the ATCwatch.ino file and compile. Done
Simply select the DaFit as the board and click on compile, you will get an Update file you can flash in the Arduino folder.

Please make shure you have always an option to go back to Bootlaoder somehow, i can only suggest to have one watch opened and connected an SWD St-Link V2 to it to develope on that.


#### This can be flashed without opening the Watch with this Repo https://github.com/atc1441/DaFlasherFiles and the DaFlasher app from the PlayStore(Android):
https://play.google.com/store/apps/details?id=com.atcnetz.paatc.patc&hl=en_US

https://www.youtube.com/watch?v=gUVEz-pxhgg

This firmware is meant to be used with the D6Notification App from the PlayStore(Android):
https://play.google.com/store/apps/details?id=com.atcnetz.de.notification&hl=gsw

## License:
You can use and edit the code as long as you mention me (Aaron Christophel and https://ATCnetz.de) in the source and somewhere in the menu of the working firmware, even when using small peaces of the code. :)
If you want to use the code or parts of it commercial please write an email to: info@atcnetz.de

## Credits:
Many Thanks to Daniel Thompson(https://github.com/daniel-thompson/wasp-os) to giving the Hint with the BMA423 Library
This way interrupts are finally possible with it.

This code uses the BMA423 Library wich is made by Bosch and this is under copyright by Bosch Sensortech GmbH
https://github.com/BoschSensortec/BMA423-Sensor-API
