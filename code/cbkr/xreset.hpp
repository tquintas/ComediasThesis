#ifndef XRESET_H
#define XRESET_H

#include "xpreparation.hpp"

namespace bkr
{
    //Class for the Reset preparation
    class XReset : public XPreparation
    {
        public:
            //Constructor
            XReset(XAttribute* id, XAttribute* name);
            //Modify preparation (Not allowed)
            void Mod();
    };
}

#endif