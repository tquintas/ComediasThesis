#ifndef XDOCUMENT_H
#define XDOCUMENT_H

#include "xmaps.hpp"

namespace bkr
{
    //Class for an xml document
    class XDocument : public XNode
    {
        protected:
            XElement* root;
        public:
            //Constructors
            XDocument(XElement* xele);
            XDocument(const XDocument& other);
            XDocument(XDocument&& other);
            //Destructor
            ~XDocument();
            //Assignment
            XDocument& operator=(XDocument&& other);
            //Save the parsed xml into a .xml file
            void Save(std::string file_name = "xmlDocument.xml");
    };
}

#endif