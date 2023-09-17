#pragma once
#include <string>
#include <string_view>
#include <sstream>
#include <vector>

struct HtmlElement
{
    std::string name, text;
    std::vector<HtmlElement> elements;

    HtmlElement() {}
    HtmlElement(std::string_view name, std::string_view text) : name{name}, text{text} {}
    std::string str(int indent = 0) const {
        std::stringstream ss;
        std::string i(indent, ' ');
        ss << i << "<" << name << ">" << std::endl;
        if (text.size() > 0) ss << std::string((indent + 2), ' ') << text << std::endl;
        for (auto const& element : elements) {
            ss << element.str(indent + 2);
        }
        ss  << i << "</" << name << ">" << std::endl;
        return ss.str();
    }
};

struct HtmlBuilder
{
    HtmlElement root;
    
    HtmlBuilder(std::string_view root_name) {
        root.name = root_name;
    }
    HtmlBuilder& add_child(std::string_view child_name, std::string_view child_text) {
        root.elements.emplace_back(child_name, child_text);
        return *this;
    }
    std::string str() {
        return root.str();
    }
};