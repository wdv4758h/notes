KERNEL_VERSION    := $(shell uname -r)
KERNEL_BUILD_PATH := /lib/modules/$(KERNEL_VERSION)/build

# Name of this kernel module
KERNEL_MODULE     := hello

obj-m             += $(KERNEL_MODULE).o     # Tell kbuild which files to build

all:
	$(MAKE) -C $(KERNEL_BUILD_PATH) M=$(PWD) modules

clean:
	$(MAKE) -C $(KERNEL_BUILD_PATH) M=$(PWD) clean
