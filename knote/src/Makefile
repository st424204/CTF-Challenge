PWD := $(shell pwd) 

KERNEL_DIR   = /home/billy/KERNEL/linux-5.1.9
MODULE_NAME = note
obj-m := $(MODULE_NAME).o

all:
	make -C $(KERNEL_DIR) M=$(PWD) modules


clean:
	make -C $(KERNEL_DIR) M=$(PWD) clean


