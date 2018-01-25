import sys
import serial
print(sys.argv[1])
f = None
f = open(sys.argv[2], "w")
port = sys.argv[1]

ser = serial.Serial(port, 115200)
while True:
    data = ser.readline()
    f.write(str(data))
    print(str(data))