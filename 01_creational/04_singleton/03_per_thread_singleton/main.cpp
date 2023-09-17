#include <iostream>
#include <thread>

class PerThreadSingleton
{
public:
    std::thread::id id;
    static PerThreadSingleton& get() {
        thread_local PerThreadSingleton instance;
        return instance;
    }

private:
    PerThreadSingleton() {
        id = std::this_thread::get_id();
    }
};

int main(int argc, char** argv)
{
    std::thread t1([]() {
        std::cout << "t1: " << PerThreadSingleton::get().id << "\n";
    });
    std::thread t2([]() {
        std::cout << "t2: " << PerThreadSingleton::get().id << "\n";
        std::cout << "t2 again: " << PerThreadSingleton::get().id << "\n";
    });

    t1.join();
    t2.join();

    return 0;
}