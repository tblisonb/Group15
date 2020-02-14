import sys
import serial
import time
import threading
from gpiozero import LED

NUM_STEPS = 20
channel_A = 0
channel_B = 0
old_channel_A = 0
old_channel_B = 0
prev_change = 'B'
output_A = LED("GPIO16")
output_B = LED("GPIO20")

""" Initialize serial I/O with ATmega4809 and call parser function. """
def run(port, baud, timeout, dir, num_rotations, vel):
    print("Attempting to open port " + port + " at " + baud + " Hz.")
    ser = serial.Serial(port, baud, timeout=5)      # open port
    prev = time.time()                 # track time after opening
    print("Expected: Direction = " + str(dir) + ", Num Rotations = " + str(num_rotations) + ", Velocity = " + str(vel))
    for i in range(int(num_rotations)):
        t = threading.Thread(target=rotate, args=(vel, dir, ser))
        t.start()
        prev = time.time()  # start rotation
        s = ser.read(1)     # read char
        t.join()
        cur = time.time()   # end time
        print("Response received: " + str(cur - prev) + " ms.")
        inst_v = (float(1) / float(NUM_STEPS)) / (cur - prev) # compute velocity of turn
        result = parse_inputs(s)
        display(result, inst_v)
    ser.close()  # close port
    
""" Assuming the ATmega4809 will transmit rotary data in the format abAB
    where a and b are the previous line states on channel A and B, and AB is 
    the most recent states. Based on the change between these states, the 
    turn direciton can be determined. """
def parse_inputs(data):
    if len(data) != 1:
        return
    print(data)
    # parse hex data sent over serial
    prev_A = (ord(data) & 8) >> 3
    prev_B = (ord(data) & 4) >> 2
    new_A = (ord(data) & 2) >> 1
    new_B = (ord(data) & 1)
    print(prev_A, prev_B, new_A, new_B)
    # if clockwise turn detected from state change...
    if (
            (prev_A > new_A and prev_B == new_B and new_B == 1 or 
            prev_A < new_A and prev_B == new_B and new_B == 0) or 
            (prev_B > new_B and prev_A == new_A and new_A == 0 or 
            prev_B < new_B and prev_A == new_A and new_A == 1)
        ):
        return 'CW'
    # if counter-clockwise turn detected from state change...
    elif (
            (prev_A > new_A and prev_B == new_B and new_B == 0 or 
            prev_A < new_A and prev_B == new_B and new_B == 1) or 
            (prev_B > new_B and prev_A == new_A and new_A == 1 or 
            prev_B < new_B and prev_A == new_A and new_A == 0)
        ):
        return 'CC'
    # no change detected (since the values remained the same)
    elif prev_A == new_A and prev_B == new_B:
        return 'NT'
    # anything else is an invalid state change (shouldn't technically be possible)
    else:
        return 'IV'

""" Formats output of the turn direction & velocity. """
def display(direction, velocity):
    if direction == 'CW':
        print("Clockwise turn detected @ " + str(velocity) + " revolutions per second.")
    elif direction == 'CC':
        print("Counter-clockwise turn detected @ " + str(velocity) + " revolutions per second.")
    else:
        print("Invalid inputs (measured: direction - " + str(direction) + ", velocity - " + str(velocity) + ").")
        
""" Simulate a rotary encoder turn with a certain speed, number of rotations,
    in either the clockwise or counter-clockwise direction. """
def rotate(velocity, direction, ser):
    global prev_change
    global channel_A
    global channel_B
    if direction == 'CW':
        if prev_change == 'B':
            channel_A ^= 1
            output_A.value = channel_A
            prev_change = 'A'
            time.sleep(float(velocity) / float(NUM_STEPS))
        else:
            channel_B ^= 1
            output_B.value = channel_B
            prev_change = 'B'
            time.sleep(float(velocity) / float(NUM_STEPS))
    elif direction == 'CC':
        if prev_change == 'B':
            channel_B ^= 1
            output_B.value = channel_B
            prev_change = 'A'
            time.sleep(float(velocity) / float(NUM_STEPS))
        else:
            channel_A ^= 1
            output_A.value = channel_A
            prev_change = 'B'
            time.sleep(float(velocity) / float(NUM_STEPS))
    old_channel_A = channel_A
    old_channel_B = channel_B

def main():
    if len(sys.argv) == 7:          # check for correct command line args
        port = sys.argv[1]          # assign arg value for port
        baud = sys.argv[2]          # assign arg value for baud
        time = sys.argv[3]          # assign arg value for timeout
        dir = sys.argv[4]           # direction of turn
        num_rotations = sys.argv[5] # number of rotations to trigger
        vel = sys.argv[6]           # velocity of the turn
        run(port, baud, time, dir, num_rotations, vel)
    else:
        print("Incorrect arguments provided")
        print("Format: python encoder_simulator.py [port] [baud] [timeout] [direction] [num rotations] [velocity]")
    
if __name__ == "__main__":
    main()
