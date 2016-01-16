// clang++ -std=c++14 -Wall -Wextra -lpthread

#include <iostream> // cout, endl
#include <thread>   // thread
#include <future>   // async, promise, packaged_task

void f1() {
    std::cout << "f1 !!!" << std::endl;
}

void f2(int n) {
    std::cout << "f2 !!!" << std::endl;
}

void f3(int &n) {
    ++n;
    std::cout << "f3 !!!" << std::endl;
}

auto f4(int &n) {
    ++n;
    std::cout << "f4 !!!" << std::endl;
    return n;
}

void f5(int &n, std::promise<int> promise) {
    ++n;
    std::cout << "f5 !!!" << std::endl;
    promise.set_value(n);
}

int main() {

    const auto n = std::thread::hardware_concurrency();
    std::cout << n << " concurrent threads are supported.\n";

    ////////////////////////////////////////
    // Invoke Each Thread
    ////////////////////////////////////////

    {
        std::thread t(f1);                      // no parameter
        t.join();
    }

    {
        std::thread t(f2, 1);                   // pass by value
        t.join();
    }

    {
        int data = 42;
        std::cout << "before: " << data << std::endl;
        std::thread t(f3, std::ref(data));      // pass by reference, need std::ref
        t.join();
        std::cout << "after:  " << data << std::endl;
    }

    {
        int data = 42;
        std::cout << "before: " << data << std::endl;
        std::thread t(f4, std::ref(data));
        std::thread new_t(std::move(t));        // new_t is now running f4(), t is no longer a thread
        new_t.join();
        std::cout << "after:  " << data << std::endl;
    }

    ////////////////////////////////////////
    // Async & Future
    ////////////////////////////////////////

    {
        int data = 42;
        // explicitly use std::launch::async to force program use thread
        auto future = std::async(std::launch::async, &f4, std::ref(data));
        future.wait();
        std::cout << "result from future: " << future.get() << std::endl;
    }

    ////////////////////////////////////////
    // Promise
    ////////////////////////////////////////

    {
        int data = 42;
        std::promise<int> myPromise;
        auto future = myPromise.get_future();
        std::thread t(f5, std::ref(data), std::move(myPromise));
        future.wait();
        std::cout << "future.get(): " << future.get() << std::endl;
        t.join();
    }

    ////////////////////////////////////////
    // packaged_task
    ////////////////////////////////////////

    {
        // future from a packaged_task
        std::packaged_task<int(int, int)> task([=](int a, int b){ return a+b; }); // wrap the function
        std::future<int> future = task.get_future();    // get a future
        std::thread(std::move(task), 42, 56).detach();  // launch on a thread
        future.wait();
        std::cout << "future.get(): " << future.get() << std::endl;
    }

    {
        std::packaged_task<int(int, int)> task([=](int a, int b){ return a+b; }); // wrap the function
        std::future<int> future = task.get_future();    // get a future
        task(42, 56);   // launch on same thread, this will block
        std::cout << "future.get(): " << future.get() << std::endl;

        task.reset();                   // re-use same task object
        future = task.get_future();     // re-get the future
        std::thread(std::move(task), 43, 57).detach();  // launch on another thread
        future.wait();
        std::cout << "future.get(): " << future.get() << std::endl;
    }

    return 0;
}
