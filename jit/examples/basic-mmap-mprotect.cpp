#include <string.h>     // memcpy
#include <sys/mman.h>   // mmap
#include <iostream>     // perror

const size_t SIZE = 1024;
typedef long (*JittedFunc)(long);

// Allocates RW memory of given size and returns a pointer to it.
// On failure, prints out the error and returns NULL.
void* alloc_writable_memory(size_t size) {
    auto ptr = mmap(0,
                    size,
                    PROT_READ | PROT_WRITE,
                    MAP_PRIVATE | MAP_ANONYMOUS,
                    -1,
                    0);
    if (ptr == (void*)-1) {
        perror("mmap");
        return nullptr;
    }
    return ptr;
}

// Allocates RWX memory of given size and returns a pointer to it. On failure,
// prints out the error and returns NULL.
void* alloc_executable_memory(size_t size) {
    auto ptr = mmap(0,
                    size,
                    PROT_READ | PROT_WRITE | PROT_EXEC,
                    MAP_PRIVATE | MAP_ANONYMOUS,
                    -1,
                    0);
    if (ptr == (void*)-1) {
        perror("mmap");
        return nullptr;
    }
    return ptr;
}

// Sets a RX permission on the given memory, which must be page-aligned.
// Returns 0 on success. On failure, prints out the error and returns -1.
int make_memory_executable(void* m, size_t size) {
    if (mprotect(m, size, PROT_READ | PROT_EXEC) == -1) {
        perror("mprotect");
        return -1;
    }
    return 0;
}

void emit_code_into_memory(unsigned char* m) {
    unsigned char code[] = {
        0x48, 0x89, 0xf8,                   // mov %rdi, %rax
        0x48, 0x83, 0xc0, 0x04,             // add $4, %rax
        0xc3                                // ret
    };
    memcpy(m, code, sizeof(code));
}

// Allocates RW memory,
// emits the code into it and sets it to RX before executing.
void emit_to_rw_run_from_rx() {
    void* m = alloc_writable_memory(SIZE);
    emit_code_into_memory(static_cast<unsigned char*>(m));
    make_memory_executable(m, SIZE);

    JittedFunc func = reinterpret_cast<JittedFunc>(m);
    int result = func(2);
    printf("result = %d\n", result);
}

// Allocates RWX memory directly.
void run_from_rwx() {
    void* m = alloc_executable_memory(SIZE);
    emit_code_into_memory(static_cast<unsigned char*>(m));

    JittedFunc func = reinterpret_cast<JittedFunc>(m);
    int result = func(2);
    printf("result = %d\n", result);
}

int main() {
    run_from_rwx();             // not safe
    emit_to_rw_run_from_rx();   // safer
    return 0;
}
