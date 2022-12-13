KERNEL_PATH := /lib/modules/`uname -r`/build
PWD := $(shell pwd)
MODULE_NAME := drive

obj-m := $(MODULE_NAME).o

all:
	$(MAKE) -C $(KERNEL_PATH) M=$(PWD)

clean:
	rm -rf .*.cmd *.o *.mod.c *.order *.symvers *.tmp *.ko

