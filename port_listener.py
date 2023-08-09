import serial
import re
import subprocess

try:
    ser = serial.Serial('/dev/cu.usbmodem11401', 9600)
    print("Connected and listening to serial port 9600.")
except:
    raise "Arduino not connected!"

processes = {}

while True:
    line = ser.readline().decode('utf-8').rstrip()
    matches = re.search("Comp_([1-5])_(\d+)", line)
    if matches != None:
        chn = int(matches.groups()[0])
        comp = int(matches.groups()[1])
        processes[chn] = subprocess.run([f"./render.sh {chn} {comp}"], shell=True)
    if line == "error": break

print("Port disconnected.")
ser.close()