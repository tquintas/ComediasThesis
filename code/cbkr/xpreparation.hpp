#ifndef XPREPARATION_H
#define XPREPARATION_H

#include "xdocument.hpp"

namespace bkr
{
    //Class for a bitKlavier Preparation
    class XPreparation : public XElement
    {
        protected:
            XAttribute* ID;
            XAttribute* name;
            XAttribute* alt;
            XElement* Item;
            XElement* item;
            XAttribute* piano;
            XAttribute* active;
            XAttribute* text;
            XAttribute* type;
            //Structure for the position of the preparation
            struct {
                XAttribute* x;
                XAttribute* y;
                XAttribute* w;
                XAttribute* h;
            } position;
            XElement* connections;
            bool just_item = false;
            XAttributeMap<bool>* dirty;
            XElement* dirty_element;
            int itype;
            int mod_itype;
            bool moded;
        public:
            //Constructor
            XPreparation(XAttribute* id, XAttribute* prep_name, XName* tag_name, int type, int dn, int modtype);
            //Create the item element
            void createItem();
            //Assign the preparation to a piano
            void ChangePiano(XText* val);
            //Get the ttem element
            XElement* getItem();
            //Connect the preparation to another preparation
            void Connect(XPreparation* node);
            //Check if preparation is only an item
            bool IsJustItem();
            //Turn the preparation into a Modification
            void Mod();
            //Turn dirty some moded parameter
            void GetDirty(int i);
            //Save the preparation into bitKlavier
            void Save(std::string file_name);
    };
}

#endif