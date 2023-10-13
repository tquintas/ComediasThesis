#ifndef XMAPS_H
#define XMAPS_H

#include "xelement.hpp"

namespace bkr
{
    //Class for mappings of attributes
    //This creates a map where the keys are the tag name of the attribute
    //and the values are pointers to the attribute nodes
    //This way it's possible to automate the creation of similar attributes within
    //the same element
    template <typename T>
    class XAttributeMap : public std::map<std::string, XAttribute*>
    {
        private:
            XElement* node;
            std::string prefix;
            std::function<XAttribute*(int, T)> attr_func;
            std::function<XAttribute*(int, std::string, T)> alt_attr_func1;
            std::function<XAttribute*(std::string, T)> alt_attr_func2;
            std::function<XAttribute*(int, T, std::string)> opt_attr_func;
        public:
            //Constructors
            XAttributeMap(XElement* main_node);
            XAttributeMap(XElement* main_node, std::string fprefix, std::function<XAttribute*(int, T)> func);
            XAttributeMap(XElement* main_node, std::string fprefix, std::function<XAttribute*(int, T, std::string)> func);
            //Add a new pair to the map
            void NewPair(int key, T val);
            //Update an existing pair
            void UpdatePair(int key, T val);
            //Add a new pair with a custom option
            void NewPair(int key, T val, std::string opt);
            //Update an existing pair with a custom option
            void UpdatePair(int key, T val, std::string opt);
            //Update a custom pair
            void UpdateCustomPair(std::string key, T val);
            //Update a custom pair with the same tag name
            void UpdateCustomPair(XAttribute* xattr);
            //Add a custom pair
            void CustomPair(std::string key, T val);
            //Add a custom pair
            void CustomPair(XAttribute* xattr);
            //Add a custom pair with a prefix
            void CustomPair(int key, std::string pref, T val);
            //Getters
            XElement* getNode();
            std::string getPrefix();
            //Get main key with index i
            XAttribute* operator()(int i);
            //Get main key with index i and a prefix
            XAttribute* operator()(int i, std::string pref);
            //Iterator for the first attribute
            std::vector<XAttribute*>::iterator FirstAttribute() const;
            //Iterator for the last attribute
            std::vector<XAttribute*>::iterator LastAttribute() const;
            //Clear mapping and all attributes
            void Clear();
            //Check if any attribute has value
            bool HasValue(T val);
            //Remove all attributes with value
            void RemoveWithValue(T val);
    };

    //Class for mappings of children
    //This creates a map where the keys are the tag name of the child
    //and the values are pointers to the attribute mapping of the new child
    //This way it's possible to automate the creation of similar children inside
    //the same element, while also automating the creation of attributes
    template <typename T>
    class XElementMap : public std::map<std::string, XAttributeMap<T>*>
    {
        private:
            XElement* node;
            std::string prefix;
            std::function<XName*(int)> name_func;
            std::function<XName*(std::string)> alt_name_func1;
        public:
            //Constructors
            XElementMap(XElement* main_node);
            XElementMap(XElement* main_node, std::string fpref, std::function<XName*(int)> func);
            //Add a child and the function for the attribute mapping
            void AddElement(int key, std::string attr_pref, std::function<XAttribute*(int, T)> func);
            //Add a custom child and the function for the attribute mapping
            void AddCustomElement(std::string key, std::string attr_pref, std::function<XAttribute*(int, T)> func);
            //Add a custom child and the function for the attribute mapping
            void AddCustomElement(XName* key, std::string attr_pref, std::function<XAttribute*(int, T)> func);
            //Add a custom child with a prefix and the function for the attribute mapping
            void AddCustomElement(int key, std::string ele_pref, std::string attr_pref, std::function<XAttribute*(int, T)> func);
            //Get the child's attribute mapping by the key index
            XAttributeMap<T>* operator()(int i);
            //Get the child's attribute mapping by the key index and prefix
            XAttributeMap<T>* operator()(int i, std::string ele_pref);
            //Get the child's attribute mapping by full key
            XAttributeMap<T>* get(std::string ele_pref);
            //Get the child's attribute mapping by full key
            XAttributeMap<T>* get(XName* name);
            //Get attribute j of child i
            XAttribute* operator()(int i, int j);
            //Get attribute j of child i, with prefixes
            XAttribute* operator()(int i, int j, std::string ele_pref, std::string attr_pref);
            //Delete everything
            void Clear();
            //Delete attributes of main element
            void ClearAttributes();
            //Delete attributes of all children
            void ClearChildAttributes(XName* except = nullptr);
    };
}

#endif