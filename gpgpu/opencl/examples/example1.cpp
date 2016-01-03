// $(CXX) -O3 -lOpenCL

#include <CL/cl.hpp>

#include <iostream>
#include <vector>

// pick up device type from compiler command line or from the default type
#ifndef DEVICE
    #define DEVICE CL_DEVICE_TYPE_DEFAULT
#endif

const char* opencl_source = "\
__kernel void cl_add(__global int *a,\
                     __global int *b,\
                     __global int *c) {\
    int i = get_global_id(0);\
    c[i] = a[i] + b[i];\
}\
";

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
    cl::Program program(context, opencl_source, true);     // true to build ...

    // Create the kernel functor
    cl::make_kernel<cl::Buffer, cl::Buffer, cl::Buffer> cl_add(program, "cl_add");

    // Get the command queue
    cl::CommandQueue queue(context);
    cl::Event event;

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

    for (int i = 0; i < c.size(); i++) {
        std::cout << c[i] << std::endl;
    }

    return 0;
}
