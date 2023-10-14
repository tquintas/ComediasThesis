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
            XAttributeMap(XElement* main_node) : node(main_node)
            {
                prefix = "";
                alt_attr_func1 = [](int i, std::string pref, T val) { return new XAttribute(pref+to_string(i), to_string(val)); };
                alt_attr_func2 = [](std::string pref, T val) { return new XAttribute(pref, to_string(val)); };
            };
            XAttributeMap(XElement* main_node, std::string fprefix, std::function<XAttribute*(int, T)> func) : node(main_node)
            {
                attr_func = func;
                prefix = fprefix;
                alt_attr_func1 = [](int i, std::string pref, T val) { return new XAttribute(pref+to_string(i), to_string(val)); };
                alt_attr_func2 = [](std::string pref, T val) { return new XAttribute(pref, to_string(val)); };
            };
            XAttributeMap(XElement* main_node, std::string fprefix, std::function<XAttribute*(int, T, std::string)> func) : node(main_node)
            {
                opt_attr_func = func;
                prefix = fprefix;
                alt_attr_func1 = [](int i, std::string pref, T val) { return new XAttribute(pref+to_string(i), to_string(val)); };
                alt_attr_func2 = [](std::string pref, T val) { return new XAttribute(pref, to_string(val)); };
            };
            //Add a new pair to the map
            void NewPair(int key, T val)
            {
                if (!attr_func) return; 
                (*this)[prefix+std::to_string(key)] = node->setAttribute(attr_func(key, val));
            };
            //Update an existing pair
            void UpdatePair(int key, T val)
            {
                if ((*this)[prefix+std::to_string(key)])
                {
                    (*this)[prefix+std::to_string(key)]->setValue(to_string(val));
                }
                else
                {
                    NewPair(key, val);
                }
            };
            //Add a new pair with a custom option
            void NewPair(int key, T val, std::string opt)
            {
                if (!opt_attr_func) return;
                (*this)[prefix+opt+std::to_string(key)] = node->setAttribute(opt_attr_func(key, val, opt));
            };
            //Update an existing pair with a custom option
            void UpdatePair(int key, T val, std::string opt)
            {
                if ((*this)[prefix+opt+std::to_string(key)])
                {
                    (*this)[prefix+opt+std::to_string(key)]->setValue(to_string(val));
                }
                else
                {
                    NewPair(key, val, opt);
                }
            };
            //Update a custom pair
            void UpdateCustomPair(std::string key, T val)
            {
                if ((*this)[key])
                {
                    (*this)[key]->setValue(to_string(val));
                }
                else
                {
                    CustomPair(key, val);
                }
            };
            //Update a custom pair with the same tag name
            void UpdateCustomPair(XAttribute* xattr)
            {
                std::string key = xattr->getComparisonString();
                if ((*this)[key])
                {
                    (*this)[key]->setValue(xattr->getValue());
                }
                else
                {
                    CustomPair(xattr);
                }
            };
            //Add a custom pair
            void CustomPair(std::string key, T val)
            {
                (*this)[key] = node->setAttribute(alt_attr_func2(key, val));
            };
            //Add a custom pair
            void CustomPair(XAttribute* xattr)
            {
                std::string key = xattr->getComparisonString();
                (*this)[key] = node->setAttribute(xattr);
            };
            //Add a custom pair with a prefix
            void CustomPair(int key, std::string pref, T val)
            {
                (*this)[pref+std::to_string(key)] = node->setAttribute(alt_attr_func1(key, pref, val));
            };
            //Getters
            XElement* getNode()
            {
                return node;
            };
            std::string getPrefix()
            {
                return prefix;
            };
            //Get main key with index i
            XAttribute* operator()(int i)
            {
                return (*this)[prefix+to_string(i)];
            };
            //Get main key with index i and a prefix
            XAttribute* operator()(int i, std::string pref)
            {
                return (*this)[pref+to_string(i)];
            };
            //Iterator for the first attribute
            std::vector<XAttribute*>::iterator FirstAttribute() const
            {
                std::vector<XAttribute*> attrs;
                attrs.reserve(this->size());
                for (const auto& kp : *this)
                {
                    attrs.push_back(kp.second);
                }
                return attrs.begin();
            };
            //Iterator for the last attribute
            std::vector<XAttribute*>::iterator LastAttribute() const
            {
                std::vector<XAttribute*> attrs;
                attrs.reserve(this->size());
                for (const auto& kp : *this)
                {
                    attrs.push_back(kp.second);
                }
                return attrs.end();
            };
            //Clear mapping and all attributes
            void Clear()
            {
                for (const auto& kp : *this)
                {
                    node->removeAttribute(kp.second);
                }
                this->clear();
            }
            //Check if any attribute has value
            bool HasValue(T val)
            {
                for (const auto& kp : *this) if (to_string(val) == to_string(*kp.second->getValue())) return true;
                return false;
            }
            //Remove all attributes with value
            void RemoveWithValue(T val)
            {
                for (const auto& kp : *this)
                {
                    if (to_string(val) == to_string(*kp.second->getValue()))
                    {
                        node->removeAttribute(kp.second);
                        this->erase(kp.first);
                    }
                }
            }
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
            XElementMap(XElement* main_node) : node(main_node)
            {
                prefix = "";
                alt_name_func1 = [](std::string pref) { return new XName(pref); };
            }
            XElementMap(XElement* main_node, std::string fpref, std::function<XName*(int)> func) : node(main_node)
            {
                prefix = fpref;
                name_func = func;
                alt_name_func1 = [](std::string pref) { return new XName(pref); };
            };
            //Add a child and the function for the attribute mapping
            void AddElement(int key, std::string attr_pref, std::function<XAttribute*(int, T)> func)
            {
                if (!name_func) return;
                std::string t = prefix+std::to_string(key);
                if (this->count(t)) return;
                XElement* new_node = new XElement(name_func(key), 0);
                node->appendChild(new_node);
                (*this)[t] = new XAttributeMap<T>(new_node, attr_pref, func);
            };
            //Add a custom child and the function for the attribute mapping
            void AddCustomElement(std::string key, std::string attr_pref, std::function<XAttribute*(int, T)> func)
            {
                std::string t = key;
                if (this->count(t)) return;
                XElement* new_node = new XElement(alt_name_func1(t), 0);
                node->appendChild(new_node);
                (*this)[t] = new XAttributeMap<T>(new_node, attr_pref, func);
            };
            //Add a custom child and the function for the attribute mapping
            void AddCustomElement(XName* key, std::string attr_pref, std::function<XAttribute*(int, T)> func)
            {
                std::string t = key->xml();
                if (this->count(t)) return;
                XElement* new_node = new XElement(alt_name_func1(t), 0);
                node->appendChild(new_node);
                (*this)[t] = new XAttributeMap<T>(new_node, attr_pref, func);
            };
            //Add a custom child with a prefix and the function for the attribute mapping
            void AddCustomElement(int key, std::string ele_pref, std::string attr_pref, std::function<XAttribute*(int, T)> func)
            {
                std::string t = ele_pref+std::to_string(key);
                if (this->count(t)) return;
                XElement* new_node = new XElement(alt_name_func1(t), 0);
                node->appendChild(new_node);
                (*this)[t] = new XAttributeMap<T>(new_node, attr_pref, func);
            };
            //Get the child's attribute mapping by the key index
            XAttributeMap<T>* operator()(int i)
            {
                return (*this)[prefix+to_string(i)];
            };
            //Get the child's attribute mapping by the key index and prefix
            XAttributeMap<T>* operator()(int i, std::string ele_pref)
            {
                return (*this)[ele_pref+to_string(i)];
            };
            //Get the child's attribute mapping by full key
            XAttributeMap<T>* get(std::string ele_pref)
            {
                return (*this)[ele_pref];
            };
            //Get the child's attribute mapping by full key
            XAttributeMap<T>* get(XName* name)
            {
                return (*this)[name->xml()];
            };
            //Get attribute j of child i
            XAttribute* operator()(int i, int j)
            {
                std::string attr_pref = (*this)[prefix+to_string(i)]->getPrefix();
                return (*(*this)[prefix+to_string(i)])[attr_pref+to_string(j)];
            };
            //Get attribute j of child i, with prefixes
            XAttribute* operator()(int i, int j, std::string ele_pref, std::string attr_pref)
            {
                return (*(*this)[ele_pref+to_string(i)])[attr_pref+to_string(j)];
            };
            //Delete everything
            void Clear()
            {
                this->clear();
                node->ClearChildren();
            }
            //Delete attributes of main element
            void ClearAttributes()
            {
                for (auto it = this->begin(); it != this->end(); ++it)
                {
                    it->second->Clear();
                }
            };
            //Delete attributes of all children
            void ClearChildAttributes(XName* except = nullptr)
            {
                std::string comp = except == nullptr ? "" : except->getComparisonString();
                for (auto it = node->FirstChild(); it != node->LastChild(); ++it)
                {
                    if ((*it)->getComparisonString() == comp) continue;
                    (*it)->ClearAttributes();
                };
            }
    };
}

#endif