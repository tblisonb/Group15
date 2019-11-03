import sys
import serial
import time

def init(port, baud):
    print("Attempting to open port " + port + " at " + baud + " Hz.")
    ser = serial.Serial(port, baud)     # open port
    print("Successfully opened port: " + ser.name)
    start = time.time()                 # track time after opening
    while (time.time() - start < 5):    # timeout after 5 seconds
        s = ser.read(20)                # read first 20 characters in buffer
        print(s)                        # print them to the terminal
    ser.close()                         # close port

def main():
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