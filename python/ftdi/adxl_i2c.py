#! /usr/bin/python

from i2cdevice import I2CDevice
from struct import unpack
import time

class ADXL_I2C(I2CDevice):
    """A driver for adxl345 over I2C"""
    ADXL_ADDRESS    = 0x53
    REG_POWER_CTL   = 0x2d
    REG_DATA_FORMAT = 0x31
    REG_DATA_X0     = 0x32
    REG_DATA_X1     = 0x33
    REG_DATA_Y0     = 0x34
    REG_DATA_Y1     = 0x35
    REG_DATA_Z0     = 0x36
    REG_DATA_Z1     = 0x37
    def __init__(self, adxl_address = 0x53):
        super(ADXL_I2C, self).__init__(adxl_address)
        #some setup
        self.writeTo(self.REG_DATA_FORMAT, 0x1)
        self.writeTo(self.REG_POWER_CTL, 0x8)

    def read_acceleration(self):
        x0 = self.readFrom(self.REG_DATA_X0, 1)
        x1 = self.readFrom(self.REG_DATA_X1, 1)
        y0 = self.readFrom(self.REG_DATA_Y0, 1)
        y1 = self.readFrom(self.REG_DATA_Y1, 1)
        z0 = self.readFrom(self.REG_DATA_Z0, 1)
        z1 = self.readFrom(self.REG_DATA_Z1, 1)

        print "x:", unpack('<h', x0+x1), \
              "y:", unpack('<h', y0+y1), \
              "z:", unpack('<h', z0+z1)
        return None

    def XXXXXX_read_acceleration(self):
        """Experimental code for getting multi-read working """
        x0 = self.readFrom(self.REG_DATA_X0, 1)
        time.sleep(0.1)
        x1 = self.readFrom(self.REG_DATA_X1, 1)
        time.sleep(0.1)

        x0x1 = self.readMultiple(self.REG_DATA_X0, 2)
        time.sleep(0.1)
        allRegs = self.readMultiple(self.REG_DATA_X0, 6)

        print "parts ord", ord(x0), ord(x1)
        print " whole ord", ord(x0x1[0]), ord(x0x1[1])
        print " parts x:", unpack('<h', x0+x1)
        print " whole x:", unpack('<h', x0x1)
        print "---All Regs", unpack('<3h', allRegs)

        return None

if __name__ == "__main__":
    driver = ADXL_I2C()
    for i in xrange(2000):
        #import ipdb; ipdb.set_trace()
        try:
            driver.read_acceleration()
            
        except Exception, e:
            print e
