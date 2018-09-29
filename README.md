# DOS fortune
This is a fortune clone for DOS. It also includes almost 1MB of textfiles 
bringing thousands of cookies with it. 

# Screenshot
![ScreenShot](https://raw.githubusercontent.com/spacerace/dos-fortune/master/screenshot.png)
 
# Installing and Running it
FORTUNE.COM must be called together with the path to the folder with all 
cookies and FORTUNE.CFG. Example: 
```
C:\GAMES\FORTUNE\FORTUNE.COM C:\GAMES\FORTUNE\
```
The folder C:\GAMES\FORTUNE needs this content: 
* FORTUNE.COM
* FORTUNE.CFG
* all the files listed in FORTUNE.CFG (cookie-files) 

These files can be found in subfolder "files". 
Here in source's root folder I also supply "fortune.zip", which is a complete 
package of FORTUNE and all COOKIE-FILES. 
Simply unpack to a folder and call it. 
 
# FORTUNE.CFG and COOKIE-FILES
Fortune files are standard unix-fortune files. Every cookie can be more than 
one line. They are seperated by '%' character. 
The config file only holds filenames of cookie files. Every line is one cookie- 
file. 

# Emulating it (dosbox)
On linux-systems you can use my makefile for starting dosbox, it does autostart
fortune.
```
$ make dosbox
``` 
If you don't have it installed, here's how to do that on debian (ubuntu): 
```
$ apt-get install dosbox
```
 
# Speed issues
This is quite slow, needs to be improved with database files rather than
counting every cookie file all the time again and again... 
 
# Building it 
 
You'll only need "dev86 / bcc" and "make"
```
$ apt-get install bcc make
``` 
There are different targets for make: 
- all 
- dosbox 

all builds x86-pong. 
dosbox starts dosbox with my provided dosbox.conf 

# License
Fortune code is totally written by me, it comes under terms of GPL-v2. 
Cookie-files are taken from gentoo-project, *TODO* document licenses for these. 
