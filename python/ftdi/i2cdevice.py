'''
An example of interfacing to ADXL345 through I2C with FTDI chip 
'''

from mpsse import I2C, FOUR_HUNDRED_KHZ, MSB, ACK, MPSSE

class I2CDevice(object):
    def __init__(self, deviceAddress, device=None):
        self.writeAddress = chr(deviceAddress << 1)
        self.readAddress = chr((deviceAddress << 1) | 1)
        if device is None:
            self.device = MPSSE(I2C, FOUR_HUNDRED_KHZ, MSB)

    def cleanup(self):
        self.device.Close()

    def readFrom(self, reg, length):
        data = None
        self.pointToDevRegister(reg)
        dev = self.device
        dev.Start()
        dev.Write(self.readAddress)
        if dev.GetAck() != ACK:
            raise Exception("(%s) Ack failed after read register write" % dev.GetDescription())
        #dev.SetAck(1)
        dev.SendNacks() #SetAck(1) is really SendNacks
        data = dev.Read(length)

        #dev.SendNacks() #why sent nacks again?
        dev.Stop()
        return data

    def readMultiple(self, reg, length):

        data = ''
        self.pointToDevRegister(reg)
        dev = self.device
        dev.Start()
        dev.Write(self.readAddress)
        if dev.GetAck() != ACK:
            raise Exception("(%s) Ack failed after read register write" % dev.GetDescription())
        #dev.SetAck(1)
        while (len(data) < length):

            dev.SendAcks()
            data += dev.Read(1)

        dev.SendNacks()
        dev.Stop()
        return data



    def writeTo(self, register, value):
        self.pointToDevRegister(register)
        dev = self.device
        dev.Write(chr(value))
        if dev.GetAck() != ACK:
            raise Exception("(%s) Ack failed after writing value" % dev.GetDescription())
        dev.Stop()

    def pointToDevRegister(self, register):
        dev = self.device
        dev.Start()
        dev.Write(self.writeAddress)
        if dev.GetAck() == ACK:
            dev.Write(chr(register))
            if dev.GetAck() != ACK:
                raise Exception("(%s) Second Ack failed" % dev.GetDescription())
        else:
            raise Exception("(%s) First Ack failed" % dev.GetDescription())
            
if __name__ == '__main__':
    i2c = I2CDevice(0x53)
    print "reg 0: %r" % i2c.readFrom(0, 1)
    print "reg 0x1e: %r" % i2c.readFrom(0x1e, 1)
    print "writing to 0x1e"
    i2c.writeTo(0x1e, 3)
    print "reg 0x1e: %r" % i2c.readFrom(0x1e, 1)



