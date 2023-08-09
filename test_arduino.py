import serial
import subprocess

try:
    ser = serial.Serial('/dev/cu.usbmodem11401', 9600)
    print("Connection success!")
except:
    print("Error! Wrong port or Arduino not connected! Check if the Arduino is connected. If so, changes on the port_listener.py file must be made! Change to the right port:\n")
    subprocess.run(["ls /dev/cu.*"], shell=True)