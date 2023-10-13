#ifndef XTEXT_H
#define XTEXT_H

#include "xnode.hpp"

namespace bkr
{
    //Class for any text on xml nodes
    class XText : public XNode
    {
        private:
            std::string* content = new std::string;
        public:
            //Constructors
            XText(std::string str);
            XText(const XText& other);
            //Destructor
            ~XText() {};
            //Set the text
            void setContent(std::string* cont);
            //Get the text
            std::string* getContent();
            //Parse the xml
            std::string xml() override;
            //Convert to string
            friend std::string to_string(const XText& other);
            //Concatenate xml texts
            template <typename T> XText operator+(const T& other) const;
            //Check to see if has descendant of type, and return it
            std::pair<bool, XNode*> has_descendant(XNode* xnode) override;
            //Copy node
            XNode* copy() override;
    };

}

#endif