#ifndef XPIANO_H
#define XPIANO_H

#include "xpreparation.hpp"

namespace bkr
{
    //Class for the Piano preparation
    class XPiano : public XPreparation
    {
        protected:
            std::vector<XPreparation*> preparations;
        public:
            //Constructor
            XPiano(XAttribute* id, XAttribute* name);
            //Add a preparation to the piano
            void AddPreparation(XPreparation* prep);
            //Attach a Keymap to change pianos
            void TriggeredBy(XPreparation* keynote);
            //Iterator for first preparation of the piano
            std::vector<XPreparation*>::iterator BeginPreparations();
            //Iterator for last preparation of the piano
            std::vector<XPreparation*>::iterator EndPreparations();
            //Modify the preparation (Not allowed)
            void Mod();
    };

}

#endif