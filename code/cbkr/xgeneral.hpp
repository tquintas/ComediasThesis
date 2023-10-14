#ifndef XGENERAL_H
#define XGENERAL_H

#include "xpreparation.hpp"

namespace bkr
{
    //Class for the Compressor general element
    class XCompressor : public XElement
    {
        protected:
            XAttribute* name;
            XAttributeMap<Params>* attrs;
        public:
            //Constructor
            XCompressor(XAttribute* c_name);
            //Set the default parameters
            void DefaultParamAttributes();
            //Set a parameter
            void SetParamAttribute(XAttribute* xattr);
            //Set a parameter
            template <typename T>
            void SetParamAttribute(std::string key, T value);
    };

    //Class for the Equalizer general element
    class XEqualizer : public XElement
    {
        protected:
            XAttributeMap<Params>* attrs;
        public:
            //Constructor
            XEqualizer();
            //Set the default parameters
            void DefaultParamAttributes();
            //Set a parameter
            void SetParamAttribute(XAttribute* xattr);
            //Set a parameter
            template <typename T>
            void SetParamAttribute(std::string key, T value);
    };

    //Class for the General general element
    class XGeneral : public XElement
    {
        protected:
            XAttributeMap<Params>* attrs;
        public:
            //Construcotr
            XGeneral();
            //Set the default parameters
            void DefaultParamAttributes();
            //Set a parameter
            void SetParamAttribute(XAttribute* xattr);
            //Set a parameter
            template <typename T>
            void SetParamAttribute(std::string key, T value);
    };

}

#endif