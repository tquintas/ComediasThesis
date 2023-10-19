#ifndef XNODE_H
#define XNODE_H

#include "xml.hpp"

namespace bkr
{
    //Class for any xml Node
    class XNode
    {
        private:
            std::string offset;
            XNode* parent;
        public:
            //Constructors
            XNode();
            XNode(const XNode& other);
            //Destructor
            ~XNode();
            //Set offset to beautify
            void setOffset(std::string off);
            //Get offset to beautify
            std::string getOffset();
            //Parent related methods
            void setParent(XNode* par);
            XNode* getParent();
            //Get level of hierarchy
            int getDepth(int i = 0);
            //Compare 2 nodes
            bool operator==(XNode* other);
            //Parse the xml
            virtual std::string xml();
            //String to compare nodes
            virtual std::string getComparisonString();
            //Check to see if has descendant of type, and return it
            virtual std::pair<bool, XNode*> has_descendant(XNode* xnode);
            //Get all descendants
            virtual std::vector<XNode*> Descendants();
            //Copy node
            virtual XNode* copy();
            //Erase all attributes
            virtual void ClearAttributes();
    };

}

#endif