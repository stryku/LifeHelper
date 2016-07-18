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
            class Element
            {
                std::string m_path;
                T m_value;
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
