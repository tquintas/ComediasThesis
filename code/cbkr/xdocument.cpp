#include "xdocument.hpp"

namespace bkr
{
    XDocument::XDocument(XElement* xele) : root(xele) {};
    XDocument::XDocument(const XDocument& other) : root(other.root) {};
    XDocument::XDocument(XDocument&& other) : root(other.root)
    {
        other.root = nullptr;
    };
    XDocument::~XDocument() {};
    XDocument& XDocument::operator=(XDocument&& other)
    {
        if (this != &other)
        {
            root = other.root;
            other.root = nullptr;
        };
        return *this;
    };
    void XDocument::Save(std::string file_name)
    {
        std::ofstream fs(file_name);
        if (fs.is_open())
        {
            std::string long_string = root->xml();
            int wrap = 75;
            std::stringstream ss;
            int length = 0;
            bool min_idx = false;
            int params_idx = 0;
            for (char c : long_string)
            {
                if (length >= wrap && c == ' ')
                {
                    ss << "\n";
                    ss << repeat(" ", params_idx);
                    length = 0;
                }
                else
                {
                    ss << c;
                    c == '\n' && (length = -1);
                }
                c == '<' && (min_idx = true);
                if (min_idx && c == ' ')
                {
                    params_idx = length + 1;
                    min_idx = false;
                }
                c == '>' && ((params_idx = 0) || (min_idx = false));
                length++;
            }
            fs << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
            fs << ss.str();
            std::cout << "File saved as " << file_name << "." << std::endl;
        }
        else
        {
            std::cerr << "Unable to open file " << file_name << "." << std::endl;
        };
    }
}