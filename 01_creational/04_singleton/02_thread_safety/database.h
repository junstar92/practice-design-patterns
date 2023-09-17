#pragma once
#include <atomic>
#include <mutex>

struct Database
{
    static Database& instance() {
        Database *db = _instance.load(std::memory_order_consume);
        if (!db) {
            std::scoped_lock lock(mtx);
            db = _instance.load(std::memory_order_consume);
            if (!db) {
                db = new Database();
                _instance.store(db, std::memory_order_release);
            }
        }

        return *db;
    }
    Database(Database const&) = delete;
    Database(Database&&) = delete;
    Database& operator=(Database const&) = delete;
    Database& operator=(Database&&) = delete;

    int get_population() { 
        
        return i++;
    }
protected:
    Database() {}

private:
    static std::atomic<Database*> _instance;
    static std::mutex mtx;
    int i{0};
};