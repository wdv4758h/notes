CC=mpicc
CFLAGS=-Wall -Wextra -O3
BIN_DIR=bin

%: %.c prepare
	$(CC) $(CFLAGS) $< -o $(BIN_DIR)/$@

prepare:
	mkdir -p $(BIN_DIR)
