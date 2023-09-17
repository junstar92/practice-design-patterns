#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <database.h>

int main(int argc, char** argv)
{
    int const num_threads = 5;
    std::vector<std::thread> threads;

    for (int i = 0; i < num_threads; i++) {
        threads.emplace_back([]() {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            auto& db = Database::instance();
            std::cout << db.get_population() << std::endl;
        });
    }

    for (int i = 0; i < num_threads; i++) {
        threads[i].join();
    }

    return 0;
}