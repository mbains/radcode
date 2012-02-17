obj-m += adt7470.o
obj-m += rtc.o 
obj-m += hpet.o 
obj-m += rtc-dev.o 
obj-m += rtc-interface.o
obj-m += rtc-cmos.o
obj-m += pca9532.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
