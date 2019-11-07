import sys
import serial
import time

def init(port, baud):
    print("Attempting to open port " + port + " at " + baud + " Hz.")
    ser = serial.Serial(port, baud)     # open port
    print("Successfully opened port: " + ser.name)
    start = time.time()                 # track time after opening
    while (time.time() - start < 5):    # timeout after 5 seconds
        s = ser.read(4)                # read first 20 characters in buffer
        print(s)                        # print them to the terminal
        parse_inputs(s)
    ser.close()                         # close port
    
# Assuming the ATmega4809 will transmit rotary data in the format abAB
# where a and b are the previous line states on channel A and B, and AB is 
# the most recent states. Based on the change between these states, the 
# turn direciton can be determined.
def parse_inputs(data):
    prev_A = (data & 8) >> 3
    prev_B = (data & 4) >> 2
    new_A = (data & 2) >> 1
    new_B = (data & 1)
    print(prev_A, prev_B, new_A, new_B)
    if (
            (prev_A > new_A and prev_B == new_B and new_B == 1 or 
            prev_A < new_A and prev_B == new_B and new_B == 0) or 
            (prev_B > new_B and prev_A == new_A and new_A == 0 or 
            prev_B < new_B and prev_A == new_A and new_A == 1)
        ):
        print('CW')
        return 'CW'
    elif (
            (prev_A > new_A and prev_B == new_B and new_B == 0 or 
            prev_A < new_A and prev_B == new_B and new_B == 1) or 
            (prev_B > new_B and prev_A == new_A and new_A == 1 or 
            prev_B < new_B and prev_A == new_A and new_A == 0)
        ):
        print('CC')
        return 'CC'
    elif prev_A == new_A and prev_B == new_B:
        print('NT')
        return 'NT'
    else:
        print('IV')
        return 'IV'

def main():
    ## -- TEST parse_inputs -- ##
    result0 = parse_inputs(0) # no turn
    result1 = parse_inputs(1) # counter-clockwise
    result2 = parse_inputs(2) # clockwise
    result3 = parse_inputs(3) # invalid
    result4 = parse_inputs(4) # clockwise
    result5 = parse_inputs(5) # no turn
    result6 = parse_inputs(6) # invalid
    result7 = parse_inputs(7) # counter-clockwise
    result8 = parse_inputs(8) # counter-clockwise
    result9 = parse_inputs(9) # invalid
    result10 = parse_inputs(10) # no turn
    result11 = parse_inputs(11) # clockwise
    result12 = parse_inputs(12) # invalid
    result13 = parse_inputs(13) # clockwise
    result14 = parse_inputs(14) # counter-clockwise
    result15 = parse_inputs(15) # no turn
    assert(result0 == 'NT')
    assert(result1 == 'CC')
    assert(result2 == 'CW')
    assert(result3 == 'IV')
    assert(result4 == 'CW')
    assert(result5 == 'NT')
    assert(result6 == 'IV')
    assert(result7 == 'CC')
    assert(result8 == 'CC')
    assert(result9 == 'IV')
    assert(result10 == 'NT')
    assert(result11 == 'CW')
    assert(result12 == 'IV')
    assert(result13 == 'CW')
    assert(result14 == 'CC')
    assert(result15 == 'NT')
    
    if len(sys.argv) == 5:              # check for correct command line args
        port = 0
        baud = 0
        if sys.argv[1] == "--port":
            port = sys.argv[2]          # assign arg value for port
        else:
            print("Port must be the first argument")
            exit()                      # err and exit
        if sys.argv[3] == "--baud":
            baud = sys.argv[4]          # assign arg value for port
        else:
            print("Baud must be the second argument")
            exit()                      # err and exit
        init(port, baud)
    else:
        print("Incorrect arguments provided")
        print("Format: python analysis_tool.py --port [value] --baud [rate]")
    
if __name__ == "__main__":
    main()