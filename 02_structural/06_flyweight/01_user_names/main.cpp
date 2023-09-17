#include <iostream>
#include <string>
#include <string_view>
#include <map>

typedef uint16_t key;

struct User
{
    User(std::string_view first_name, std::string_view last_name) : first_name{add(first_name)}, last_name{add(last_name)} {}

    std::string const& get_first_name() const {
        return names.find(first_name)->second;
    }

    std::string const& get_last_name() const {
        return names.find(last_name)->second;
    }

    static void info() {
        for (auto entry : names) {
            std::cout << "Key: " << entry.first << ", Value: " << entry.second << std::endl;
        }
    }

    friend std::ostream& operator<<(std::ostream& os, User const& obj) {
        return os
            << "first_name: " << obj.first_name << " " << obj.get_first_name()
            << " last_name: " << obj.last_name << " " << obj.get_last_name();
    }

protected:
    key first_name, last_name;
    static std::map<key, std::string> names;
    static key seed;
    static key add(std::string_view s) {
        auto it = std::find_if(names.begin(), names.end(), [s](auto const& p) {
            if (p.second == s) {
                return true;
            }
            return false;
        });
        if (it == names.end()) {
            names.insert({++seed, std::string(s)});
            return seed;
        }
        return it->first;
    }
};

key User::seed{};
std::map<key, std::string> User::names{};

int main(int argc, char** argv)
{
    User john_doe{"John", "Doe"};
    User jane_doe{"Jane", "Doe"};

    std::cout << "John: " << john_doe << std::endl;
    std::cout << "Jane: " << jane_doe << std::endl;

    User::info();

    return 0;
}