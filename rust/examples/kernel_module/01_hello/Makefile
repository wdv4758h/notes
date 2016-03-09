########################################
# Rust Setting
########################################

CARGO  ?= $(shell which cargo)

# http://clang.llvm.org/docs/CrossCompilation.html#target-triple
# http://llvm.org/docs/doxygen/html/Triple_8h_source.html
# <arch><sub>-<vendor>-<sys>-<abi>
TRIPLE := x86_64-unknown-none-gnu

########################################
# Linux Kernel Module Setting
########################################

KERNEL_VERSION    := $(shell uname -r)
KERNEL_BUILD_PATH := /lib/modules/$(KERNEL_VERSION)/build

# Name of this kernel module
KERNEL_MODULE     := hello

# Object Files
rust-target       := ${KERNEL_MODULE}_rust.o    # build by Cargo
obj-m             += ${KERNEL_MODULE}.o         # tell kbuild which files to build
${KERNEL_MODULE}-objs := src/module.o ${rust-target}    # let them link together

########################################
# Rules
########################################

all:
	$(CARGO) rustc --release --verbose $(CARGOFLAGS) --target="$(TRIPLE)" -- --emit obj -o $(rust-target)
	$(MAKE) -C $(KERNEL_BUILD_PATH) M=$(CURDIR) modules
	cp "$(KERNEL_MODULE).ko" "$(KERNEL_MODULE).stripped.ko" && strip "$(KERNEL_MODULE).stripped.ko"

clean:
	$(MAKE) -C $(KERNEL_BUILD_PATH) M=$(CURDIR) clean
	$(CARGO) clean
	rm -f *.d *.rlib
