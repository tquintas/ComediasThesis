#ifndef XPIANO_H
#define XPIANO_H

#include "xpreparation.hpp"

namespace bkr
{
    //Class for the Comment preparation
    class XComment : public XPreparation
    {
        public:
            //Constructor
            XComment(std::string comment);
            //Change the comment's text
            void ChangeText(std::string comment);
            //Modify preparation (Not allowed)
            void Mod();
    };

}

#endif