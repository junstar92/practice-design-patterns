#pragma once
#include <string>
#include <string_view>
#include <sstream>
#include <vector>

// Groovy-Style Builder
struct Tag
{
    std::string name;
    std::string text;
    std::vector<Tag> children;
    std::vector<std::pair<std::string, std::string>> attributes;

    friend std::ostream& operator<<(std::ostream& os, Tag const& tag) {
        os << "<" << tag.name;

        for (auto const& attr : tag.attributes)
            os << " " << attr.first << "=\"" << attr.second << "\"";

        if (tag.children.size() == 0 && tag.text.length() == 0) {
            os << "/>" << std::endl;
        }
        else {
            os << ">" << std::endl;
            if (tag.text.length()) os << tag.text << std::endl;
            for (auto const& child : tag.children)
                os << child;
            os << "</" << tag.name << ">" << std::endl;
        }

        return os;
    }

protected:
    Tag(std::string_view name, std::string_view text) : name{name}, text{text} {}
    Tag(std::string_view name, std::vector<Tag> const& children) : name{name}, children{children} {}
};

struct P : Tag
{
    explicit P(std::string_view text) : Tag{"p", text} {}
    P(std::initializer_list<Tag> children) : Tag{"p", children} {}
};

struct IMG : Tag
{
    explicit IMG(std::string_view url) : Tag{"img", ""} {
        attributes.emplace_back(std::make_pair("src", url));
    }
};