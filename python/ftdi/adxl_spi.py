#!/usr/bin/env python

from mpsse import *
from time import sleep

class ADXLSPI(object):
    WCMD        = 0
    RCMD        = "\x80"
    MULTIBYTE   = 1 << 6
    REGMASK     = 0x3f
    ADDRESS_LENGTH = 3

    def __init__(self, speed=ONE_MHZ):
        
        self.adxl = MPSSE(SPI0, speed, MSB)
        
    def _addr2str(self, address):
        addr_str = ""

        for i in range(0, self.ADDRESS_LENGTH):
                addr_str += chr((address >> (i*8)) & 0xFF)

        addr_str = addr_str[::-1]
        print "%r" % addr_str
        return addr_str 

    def readRegister(self, register):
        self.adxl.Start()
        #self.adxl.Write(chr(self.RCMD|((register)&(self.REGMASK))))
        self.adxl.Write(chr(register<<1))
        #self.adxl.Write(chr(0))
        data = self.adxl.Read(2)
        self.adxl.Stop()
        return data

    def writeRegister(self, register, value):
        self.adxl.Start()
        self.adxl.Write( chr(register << 1 & 0b01111110 | 1 ) + chr(value))
        self.adxl.Stop()

'''
void Mrf24j::write_short(byte address, byte data) {
    digitalWrite(_pin_cs, LOW);
    // 0 for top short address, 1 bottom for write
    SPI.transfer((address<<1 & 0b01111110) | 0x01);
    SPI.transfer(data);
    digitalWrite(_pin_cs, HIGH);
}
'''
import struct
if __name__ == '__main__':
    dev = ADXLSPI()
#    dev.writeRegister(0x12, 0x98)
    print "data:",  struct.unpack('bb', dev.readRegister(0x12))

