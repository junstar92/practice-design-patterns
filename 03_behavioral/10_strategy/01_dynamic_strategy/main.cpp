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

struct TextProcessor
{
    void clear() {
        oss.clear();
        oss.str("");
    }
    void append_list(std::vector<std::string> const items) {
        list_strategy->start(oss);
        for (auto& item : items) {
            list_strategy->add_list_item(oss, item);
        }
        list_strategy->end(oss);
    }
    void set_output_format(OutputFormat const format) {
        switch (format)
        {
        case OutputFormat::Markdown:
            list_strategy = std::make_unique<MarkdownListStrategy>();
            break;
        case OutputFormat::Html:
            list_strategy = std::make_unique<HtmlListStrategy>();
            break;
        default:
            throw std::runtime_error("Unsupported strategy.");
        }
    }
    std::string str() const { return oss.str(); }

private:
    std::ostringstream oss;
    std::unique_ptr<ListStrategy> list_strategy;
};

int main(int argc, char** argv)
{
    TextProcessor tp;
    // markdown
    tp.set_output_format(OutputFormat::Markdown);
    tp.append_list({"foo", "bar", "baz"});
    std::cout << tp.str() << std::endl;

    // html
    tp.clear();
    tp.set_output_format(OutputFormat::Html);
    tp.append_list({"foo", "bar", "baz"});
    std::cout << tp.str() << std::endl;

    return 0;
}