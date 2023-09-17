#include <iostream>
#include <string>
#include <string_view>
#include <vector>

class FormattedText
{
    std::string plain_text;
    bool *caps;

public:
    explicit FormattedText(std::string const& plain_text) : plain_text{plain_text} {
        caps = new bool[plain_text.length()];
    }
    ~FormattedText() {
        delete[] caps;
    }

    void capitalize(int start, int end) {
        for (int i = start; i <= end; i++) {
            caps[i] = true;
        }
    }

    friend std::ostream& operator<<(std::ostream& os, FormattedText const& obj) {
        std::string s;
        for (int i = 0; i < obj.plain_text.length(); i++) {
            char c = obj.plain_text[i];
            s += (obj.caps[i] ? std::toupper(c) : c);
        }
        return os << s;
    }
};

class BetterFormattedText
{
public:
    explicit BetterFormattedText(std::string const& plain_text) : plain_text{plain_text} {}
    struct TextRange
    {
        int start, end;
        bool capitalize{false};
        bool covers(int position) const {
            return position >= start && position <= end;
        }
    };

    TextRange& get_range(int start, int end) {
        formatting.emplace_back(TextRange{start, end});
        return formatting.back();
    }

    friend std::ostream& operator<<(std::ostream& os, BetterFormattedText const& obj) {
        std::string s;
        for (int i = 0; i < obj.plain_text.length(); i++) {
            auto c = obj.plain_text[i];
            for (auto const& rng : obj.formatting) {
                if (rng.covers(i) && rng.capitalize)
                    c = std::toupper(c);
                s += c;
            }
        }
        return os << s;
    }

private:
    std::string plain_text;
    std::vector<TextRange> formatting;
};

int main(int argc, char** argv)
{
    FormattedText ft("This is a brave new world");
    ft.capitalize(10, 15);
    std::cout << ft << std::endl;

    BetterFormattedText bft("This is a brave new world");
    bft.get_range(10, 15).capitalize = true;
    std::cout << bft << std::endl;

    return 0;
}