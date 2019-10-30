In order to run this file create a project in MPLABX and replace the main in that file with the file in this folder.
Next using the MCC plugin set the pins PF 2-4 as input with PF 4 set it to start high and PULLUPEN and set PF5 to output
Connect SW pin of a quadrature encoder to PF4 then connect the CLk and DT to PF 2 or 3, but do not connect 2 ports to 1 pin.
Lastly connect a 5V power sourc to GND and +, connect the Curiosity nano to a computer then flash the code.