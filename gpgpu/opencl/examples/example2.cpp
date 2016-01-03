// $(CXX) -Wall -Wextra -std=c++14 -O3 -lOpenCL

#include <CL/cl.hpp>

#include <iostream>
#include <fstream>  // need by ifstream
#include <vector>

// pick up device type from compiler command line or from the default type
#ifndef DEVICE
    #define DEVICE CL_DEVICE_TYPE_DEFAULT
#endif

std::string loadProgram(std::string input) {
    std::ifstream stream(input.c_str());
    if (!stream.is_open()) {
        std::cout << "Cannot open file: " << input << std::endl;
        exit(1);
    }

    return std::string(std::istreambuf_iterator<char>(stream),
                       std::istreambuf_iterator<char>());
}

int main(int argc, char *argv[]) {

    std::vector<int> a = {1, 2, 3, 4, 5};
    std::vector<int> b = {2, 3, 4, 5, 6};
    std::vector<int> c(5, 0);

    ////////////////////////////////////////
    // OpenCL
    ////////////////////////////////////////

    // Create a context
    cl::Context context(DEVICE);

    // Load in kernel source, creating a program object for the context
    cl::Program program(context, loadProgram("cl_add.cl"), true);     // true to build ...

    // Create the kernel functor
    cl::make_kernel<cl::Buffer, cl::Buffer, cl::Buffer> cl_add(program, "cl_add");

    // Get the command queue
    cl::CommandQueue queue(context);

    cl::Buffer g_a = cl::Buffer(context, a.begin(), a.end(), true);     // readOnly = True
    cl::Buffer g_b = cl::Buffer(context, b.begin(), b.end(), true);     // readOnly = True
    cl::Buffer g_c = cl::Buffer(context, c.begin(), c.end(), false);    // readOnly = False

    cl_add(
        cl::EnqueueArgs(
                queue,
                cl::NDRange(a.size())),
        g_a,
        g_b,
        g_c);

    queue.flush();
    queue.finish();

    cl::copy(queue, g_c, c.begin(), c.end());   // get result

    ////////////////////////////////////////
    // Output
    ////////////////////////////////////////

    for (size_t i = 0; i < c.size(); i++) {
        std::cout << c[i] << std::endl;
    }

    return 0;
}
