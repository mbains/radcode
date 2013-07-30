from mpsse import *
mp = MPSSE(SPI0, ONE_MHZ, MSB)
import struct 

def write_short(address, value):
    mp.Start()
    val = struct.pack('BB', (address << 1) | 1, value) 
    mp.Write(val)
    mp.Stop()
     

def read_short(address):
    mp.Start()
    mp.Write(struct.pack('B', (address << 1)))
    data = mp.Read(1)
    mp.Stop()
    return data



