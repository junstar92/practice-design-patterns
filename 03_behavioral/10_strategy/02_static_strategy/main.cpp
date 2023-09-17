#include <iostream>
#include <string>
#include <sstream>
#include <memory>

enum class OutputFormat
{
    Markdown,
    Html
};

struct ListStrategy
{
    virtual void start(std::ostringstream& oss) {};
    virtual void add_list_item(std::ostringstream& oss, std::string const& item) {};
    virtual void end(std::ostringstream& oss) {};
};

struct HtmlListStrategy : ListStrategy
{
    void start(std::ostringstream& oss) override {
        oss << "<ul>\n";
    }
    void end(std::ostringstream& oss) override {
        oss << "</ul>\n";
    }
    void add_list_item(std::ostringstream& oss, std::string const& item) override {
        oss << "  <li>" << item << "</li>\n";
    }
};

struct MarkdownListStrategy : ListStrategy
{
    void add_list_item(std::ostringstream& oss, std::string const& item) override {
        oss << " * " << item << std::endl;
    }
};

template <typename LS>
struct TextProcessor
{
    void clear() {
        oss.clear();
        oss.str("");
    }
    void append_list(std::vector<std::string> const items) {
        list_strategy.start(oss);
        for (auto& item : items) {
            list_strategy.add_list_item(oss, item);
        }
        list_strategy.end(oss);
    }
    std::string str() const { return oss.str(); }

private:
    std::ostringstream oss;
    LS list_strategy;
};

int main(int argc, char** argv)
{
    // markdown
    TextProcessor<MarkdownListStrategy> tpm;
    tpm.append_list({"foo", "bar", "baz"});
    std::cout << tpm.str() << std::endl;

    // html
    TextProcessor<HtmlListStrategy> tph;
    tph.append_list({"foo", "bar", "baz"});
    std::cout << tph.str() << std::endl;

    return 0;
}