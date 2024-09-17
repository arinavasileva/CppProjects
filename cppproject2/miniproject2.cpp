#include <iostream>
#include <fstream>
#include <mutex>
#include <memory>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <thread>

template <typename T>
class Log_Ptr {
private:
    T* ptr;                   // Pointer 
    int* ref_count;           // Reference count
    std::ofstream log_file;   // Log file
    std::mutex mtx;           // Mutex for thread safety

    // Function to log messages with a timestamp
    void log(const std::string& message) {
        auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        log_file << std::put_time(std::localtime(&now), "%Y-%m-%d %X") << " " << message << std::endl;
    }

public:
    // Constructor
    Log_Ptr(T* p) : ptr(p), ref_count(new int(1)), log_file("log_ptr.txt", std::ios::app) {
        log("ownership transferred " + std::to_string(reinterpret_cast<uintptr_t>(ptr)));
    }

    // Dereference operator
    T& operator*() {
        std::lock_guard<std::mutex> lock(mtx);
        log("operator* " + std::to_string(reinterpret_cast<uintptr_t>(ptr)));
        return *ptr;
    }

    // Arrow operator
    T* operator->() {
        std::lock_guard<std::mutex> lock(mtx);
        log("operator-> " + std::to_string(reinterpret_cast<uintptr_t>(ptr)));
        return ptr;
    }

    // copying constructor (disabled)
    Log_Ptr(const Log_Ptr&) = delete;

    // copying assignment operator (disabled)
    Log_Ptr& operator=(const Log_Ptr&) = delete;

    // moving constructor (disabled)
    Log_Ptr(Log_Ptr&&) = delete;

    // moving assignment operator (disabled)
    Log_Ptr& operator=(Log_Ptr&&) = delete;

    // Destructor
    ~Log_Ptr() {
        std::lock_guard<std::mutex> lock(mtx);  // Lock for thread safety
        if (--(*ref_count) == 0) {
            log("object destroyed " + std::to_string(reinterpret_cast<uintptr_t>(ptr)));
            delete ptr;
            delete ref_count;
        }
        log_file.close();
    }
};

// Testing log_Ptr in a single thread
void test_log_ptr() {
    // Creating a Log_Ptr object
    Log_Ptr<int> p(new int(88));

    // Dereferencing the object and printing the value
    std::cout << "Dereferenced value: " << *p << std::endl;

    // Using the arrow operator to call a member
    std::cout << "Pointer value using ->: " << *p.operator->() << std::endl;
}

// Testing log_ptr in multiple threads
void test_log_ptr_multithread() {
    Log_Ptr<int> p(new int(100));
    std::thread t1([&]() { std::cout << "Thread 1: " << *p << std::endl; });
    std::thread t2([&]() { std::cout << "Thread 2: " << *p << std::endl; });

    t1.join();
    t2.join();
}

int main() {
    // log_ptr in a single thread
    std::cout << "Testing log_ptr in a single thread:" << std::endl;
    test_log_ptr();

    // log_ptr in multiple threads
    std::cout << "\nTesting log_ptr in multiple threads:" << std::endl;
    test_log_ptr_multithread();

    return 0;
}