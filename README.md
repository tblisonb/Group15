# Group 15 - Microchip
### Group Members
* Zane Guess
* Jessica Gilbert
* Jason Guest
* Manolito Ramirez
* Tanner Lisonbee

### Project Objectives
* To develop implementations of a quadrature decoder in software, using hardware interrupts, and using the CCL peripheral found on the ATmega4809
* To analyze the differences between the implementations to demonstrate the usefulness of the CCL peripheral and how it can be used to improve the responsiveness and provided functionality of a given project
* To report on the current state of development tools, including MPLAB X and MCC in order to provide feedback and report issues found while developing for the ATmega4809
* To generate application-oriented projects which demonstrate the usefulness of the CCL peripheral

### Setting up the Software
Clone the repository, install the MPLAB X IDE from Microchip's official website or [here](https://www.microchip.com/development-tools/pic-and-dspic-downloads-archive). After downloading both, open MPLAB X and install MPLAB X Code Configurator (MCC), select open project, and navigate to where you cloned the repository. Open the project by selecting the "CoilWindFirmware.X" project file. Plug in the ATmega4809 Curiosity Nano via micro usb to your computer and click run.

### Setting up the Hardware
* Download and print the 3D models, [here](https://drive.google.com/file/d/1uZwpO_z91THDOk7w0rBcmLNLJtiAPaqZ/view?usp=sharing), after printing the parts assemble the parts.
* Purchase the requisite parts listed [here](https://drive.google.com/file/d/13glnACpHfqssd51yrxNG8hv46Ix8oQ_Q/view?usp=sharing), and assemble as shown in the provided renders of the system.
* Mount the ATmega4809 Curiosity Nano and RN4870 Click Board to the expansion board.
* Wire the quadrature encoder, stepper motor, and servo motor to the ATmega4809 as shown in the pin mappings provided in MCC.

### Final System Configuration
![System model](https://raw.githubusercontent.com/tblisonb/Group15/master/Docs/a69090e1-a111-49dc-8a19-f883155d1de0.PNG)
![System model](https://raw.githubusercontent.com/tblisonb/Group15/master/Docs/IMG_20200430_150646.jpg)
