CC=clang
PYTHON_VERSION=$(shell python --version | grep -o '[[:digit:]]\.[[:digit:]]')
CFLAGS=-Wall -Wextra -O3 -fPIC --shared -I /usr/include/python$(PYTHON_VERSION)m/

all: 01_hellomodule 02_hellomodule 03_hellomodule

%: %.c
	$(CC) $(CFLAGS) $< -o hello.so
