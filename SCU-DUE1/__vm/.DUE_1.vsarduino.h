/* 
	Editor: http://www.visualmicro.com
	        visual micro and the arduino ide ignore this code during compilation. this code is automatically maintained by visualmicro, manual changes to this file will be overwritten
	        the contents of the Visual Micro sketch sub folder can be deleted prior to publishing a project
	        all non-arduino files created by visual micro and all visual studio project or solution files can be freely deleted and are not required to compile a sketch (do not delete your own code!).
	        note: debugger breakpoints are stored in '.sln' or '.asln' files, knowledge of last uploaded breakpoints is stored in the upload.vmps.xml file. Both files are required to continue a previous debug session without needing to compile and upload again
	
	Hardware: Arduino Due (Native USB Port), Platform=sam, Package=arduino
*/

#define ARDUINO 10803
#define ARDUINO_MAIN
#define F_CPU 84000000L
#define printf iprintf
#define __SAM__
#define printf iprintf
#define F_CPU 84000000L
#define ARDUINO 10803
#define ARDUINO_SAM_DUE
#define ARDUINO_ARCH_SAM
#define __SAM3X8E__
#define USB_VID 0x2341
#define USB_PID 0x003e
#define USBCON
extern "C" void __cxa_pure_virtual() {;}

//
//

#include "C:\Users\Ludovic\AppData\Local\arduino15\packages\arduino\hardware\sam\1.6.4\variants\arduino_due_x\pins_arduino.h" 
#include "C:\Users\Ludovic\AppData\Local\arduino15\packages\arduino\hardware\sam\1.6.4\variants\arduino_due_x\variant.h" 
#include "C:\Users\Ludovic\AppData\Local\arduino15\packages\arduino\hardware\sam\1.6.4\cores\arduino\arduino.h"
#include <DUE_1.ino>
#include <Amperemetre.h>
#include <Avertisseur.h>
#include <BoiteALeviers.h>
#include <Compresseur.h>
#include <Eclairage.h>
#include <Freinage.h>
#include <Graduateur.h>
#include <Inverseur.h>
#include <LiaisonTXRX.h>
#include <ManipTraction.h>
#include <Manometre.h>
#include <NetlistDUE1.h>
#include <OpenRails.h>
#include <VACMA.h>
#include <ZPT.h>
