import sys
import serial
import time

""" Initialize serial I/O with ATmega4809 and call parser function. """
def run(port, baud, timeout):
    print("Attempting to open port " + port + " at " + baud + " Hz.")
    prev = time.time()                 # track time after opening
    while time.time() - prev < timeout:
        ser = serial.Serial(port, baud, timeout=5)     # open port
        prev = time.time()                 # start time
        s = ser.read(1)                     # read char
        cur = time.time()   # end time
        inst_v = (1 / 20) / (cur - prev) # compute velocity of turn
        result = parse_inputs(s)
        self.display(result, inst_v)
        ser.close()                         # close port
    
""" Assuming the ATmega4809 will transmit rotary data in the format abAB
    where a and b are the previous line states on channel A and B, and AB is 
    the most recent states. Based on the change between these states, the 
    turn direciton can be determined. """
def parse_inputs(data):
    prev_A = (int(data) & 8) >> 3
    prev_B = (int(data) & 4) >> 2
    new_A = (int(data) & 2) >> 1
    new_B = (int(data) & 1)
    if (
            (prev_A > new_A and prev_B == new_B and new_B == 1 or 
            prev_A < new_A and prev_B == new_B and new_B == 0) or 
            (prev_B > new_B and prev_A == new_A and new_A == 0 or 
            prev_B < new_B and prev_A == new_A and new_A == 1)
        ):
        return 'CW'
    elif (
            (prev_A > new_A and prev_B == new_B and new_B == 0 or 
            prev_A < new_A and prev_B == new_B and new_B == 1) or 
            (prev_B > new_B and prev_A == new_A and new_A == 1 or 
            prev_B < new_B and prev_A == new_A and new_A == 0)
        ):
        return 'CC'
    elif prev_A == new_A and prev_B == new_B:
        return 'NT'
    else:
        return 'IV'

""" Formats output of the turn direction & velocity. """
def display(direction, velocity):
    if direction == CW:
        print("Clockwise turn detected @ " + velocity + " revolutions per second.")
    elif direction == CC:
        print("Counter-clockwise turn detected @ " + velocity + " revolutions per second.")
    else:
        print("Invalid inputs (measured: direction - " + direction + ", velocity - " + velocity + ").")

def main():
    """## -- TEST parse_inputs -- ##
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
    assert(result15 == 'NT')"""
    
    if len(sys.argv) == 4:          # check for correct command line args
        port = sys.argv[1]          # assign arg value for port
        baud = sys.argv[2]          # assign arg value for baud
        time = sys.argv[3]          # assign arg value for timeout
        run(port, baud, time)
    else:
        print("Incorrect arguments provided")
        print("Format: python analysis_tool.py [port] [baud] [timeout]")
    
if __name__ == "__main__":
    main()