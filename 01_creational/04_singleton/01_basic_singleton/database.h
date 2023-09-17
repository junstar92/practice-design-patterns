#pragma once

struct Database
{
    static Database& get() {
        // thread-safe since C++11
        //static Database database;
        static Database* database = new Database();
        return *database;
    }
    Database(Database const&) = delete;
    Database(Database&&) = delete;
    Database& operator=(Database const&) = delete;
    Database& operator=(Database&&) = delete;
protected:
    Database() {}
};