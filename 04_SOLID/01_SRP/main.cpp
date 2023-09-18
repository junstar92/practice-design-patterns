#include <iostream>
#include <string>
#include <vector>
#include <fstream>

struct Journal
{
    std::string title;
    std::vector<std::string> entries;
    explicit Journal(std::string const& title) : title{title} {}

    void add(std::string const& entry) {
        static int count = 1;
        entries.push_back(std::to_string(count++) + ": " + entry);
    }

    void save(std::string const& filename) {
        std::ofstream ofs(filename);
        for (auto& s : entries) {
            ofs << s << std::endl;
        }
    }
};

struct PersistenceManager
{
    static void save(Journal const& j, std::string const& filename) {
        std::ofstream ofs(filename);
        for (auto& s : j.entries) {
            ofs << s << std::endl;
        }
    }
};

int main(int argc, char** argv)
{
    // Single Responsibility Principle (SRP)
    Journal j{"Dear Diary"};
    j.add("I cried today");
    j.add("I ate a bug");
    
    // It makes sense to have 'add' function as part of the 'Journal' class
    // because adding a journal entry is somthing the journal actually needs to do it.
    // But 'save' function is problematic. The Journal's responsibility is to keep journal entries,
    // not to write them to disk.
    // If you add disk-writing functionality to Journal and similar classes, any change in the approach
    // to persistence would require lots of tiny changes in each of the affected classes.
    
    // j.save("my diary.txt");
    PersistenceManager::save(j, "my diary.txt");

    return 0;
}