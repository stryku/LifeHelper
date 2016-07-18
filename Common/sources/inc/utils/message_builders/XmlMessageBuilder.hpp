#pragma once

#include <utils/traits/traits.hpp>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include <string>
#include <sstream>

namespace utils
{
    namespace MessageBuild
    {
        namespace Xml
        {
            template <typename T>
            struct Element
            {
                Element() = default;
                Element(const std::string &path, const T &value) :
                    path(path),
                    value(value)
                {}

                std::string path;
                T value;
            };

            class Builder
            {
            public:
                template <typename T>
                Builder& addElement(const Element<T> &elem)
                {
                    tree.put(elem.path, toString(elem.value));

                    return *this;
                }

                template <typename Container>
                Builder& addElements(const Container &elements)
                {
                    for (const auto &element : elements)
                        addElement(element);

                    return *this;
                }

                std::string build() const
                {
                    std::ostringstream oss;
                    boost::property_tree::write_xml(oss, tree);

                    return oss.str();
                }

            private:
                boost::property_tree::ptree tree;
            };
        }
    }
}
