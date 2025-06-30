import zmq
import time
import struct
import random




context = zmq.Context()
socket = context.socket(zmq.PUB)
socket.bind("tcp://*:5555")

while True:
    # '<' means little-endian, standard sizes, no padding
    price = 182.34 + random.uniform(-1, 1)
    size = random.randint(50, 150)
    data = struct.pack('<4sdIQ', b'AAPL', price, size, int(time.time_ns()))
    print(data)
    socket.send(data)
    time.sleep(0.001)
    
    
