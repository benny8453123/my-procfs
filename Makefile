#CONFIG_MODULE_SIG=n

obj-m				+= procfs-test-module.o
procfs-test-module-objs		:= my-procfs.o

#CC=gcc
KVERSION = $(shell uname -r)
KERNEL_DIR := /lib/modules/$(KVERSION)/build

all:
	$(MAKE) -C $(KERNEL_DIR) M=$(PWD) modules
clean:
	$(MAKE) -C $(KERNEL_DIR) M=$(PWD) clean
