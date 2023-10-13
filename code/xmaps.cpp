#include "xmaps.hpp"

namespace bkr
{
    template <typename T>
    XAttributeMap<T>::XAttributeMap(XElement* main_node) : node(main_node)
    {
        prefix = "";
        alt_attr_func1 = [](int i, std::string pref, T val) { return new XAttribute(pref+to_string(i), to_string(val)); };
        alt_attr_func2 = [](std::string pref, T val) { return new XAttribute(pref, to_string(val)); };
    };
    template <typename T>
    XAttributeMap<T>::XAttributeMap(XElement* main_node, std::string fprefix, std::function<XAttribute*(int, T)> func) : node(main_node)
    {
        attr_func = func;
        prefix = fprefix;
        alt_attr_func1 = [](int i, std::string pref, T val) { return new XAttribute(pref+to_string(i), to_string(val)); };
        alt_attr_func2 = [](std::string pref, T val) { return new XAttribute(pref, to_string(val)); };
    };
    template <typename T>
    XAttributeMap<T>::XAttributeMap(XElement* main_node, std::string fprefix, std::function<XAttribute*(int, T, std::string)> func) : node(main_node)
    {
        opt_attr_func = func;
        prefix = fprefix;
        alt_attr_func1 = [](int i, std::string pref, T val) { return new XAttribute(pref+to_string(i), to_string(val)); };
        alt_attr_func2 = [](std::string pref, T val) { return new XAttribute(pref, to_string(val)); };
    };
    template <typename T>
    void XAttributeMap<T>::NewPair(int key, T val)
    {
        if (!attr_func) return; 
        (*this)[prefix+std::to_string(key)] = node->setAttribute(attr_func(key, val));
    };
    template <typename T>
    void XAttributeMap<T>::UpdatePair(int key, T val)
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
    template <typename T>
    void XAttributeMap<T>::NewPair(int key, T val, std::string opt)
    {
        if (!opt_attr_func) return;
        (*this)[prefix+opt+std::to_string(key)] = node->setAttribute(opt_attr_func(key, val, opt));
    };
    template <typename T>
    void XAttributeMap<T>::UpdatePair(int key, T val, std::string opt)
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
    template <typename T>
    void XAttributeMap<T>::UpdateCustomPair(std::string key, T val)
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
    template <typename T>
    void XAttributeMap<T>::UpdateCustomPair(XAttribute* xattr)
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
    template <typename T>
    void XAttributeMap<T>::CustomPair(std::string key, T val)
    {
        (*this)[key] = node->setAttribute(alt_attr_func2(key, val));
    };
    template <typename T>
    void XAttributeMap<T>::CustomPair(XAttribute* xattr)
    {
        std::string key = xattr->getComparisonString();
        (*this)[key] = node->setAttribute(xattr);
    };
    template <typename T>
    void XAttributeMap<T>::CustomPair(int key, std::string pref, T val)
    {
        (*this)[pref+std::to_string(key)] = node->setAttribute(alt_attr_func1(key, pref, val));
    };
    template <typename T>
    XElement* XAttributeMap<T>::getNode()
    {
        return node;
    };
    template <typename T>
    XAttribute* XAttributeMap<T>::operator()(int i)
    {
        return (*this)[prefix+to_string(i)];
    };
    template <typename T>
    XAttribute* XAttributeMap<T>::operator()(int i, std::string pref)
    {
        return (*this)[pref+to_string(i)];
    };
    template <typename T>
    std::string XAttributeMap<T>::getPrefix()
    {
        return prefix;
    };
    template <typename T>
    std::vector<XAttribute*>::iterator XAttributeMap<T>::FirstAttribute() const
    {
        std::vector<XAttribute*> attrs;
        attrs.reserve(this->size());
        for (const auto& kp : *this)
        {
            attrs.push_back(kp.second);
        }
        return attrs.begin();
    };
    template <typename T>
    std::vector<XAttribute*>::iterator XAttributeMap<T>::LastAttribute() const
    {
        std::vector<XAttribute*> attrs;
        attrs.reserve(this->size());
        for (const auto& kp : *this)
        {
            attrs.push_back(kp.second);
        }
        return attrs.end();
    };
    template <typename T>
    void XAttributeMap<T>::Clear()
    {
        for (const auto& kp : *this)
        {
            node->removeAttribute(kp.second);
        }
        this->clear();
    }
    template <typename T>
    bool XAttributeMap<T>::HasValue(T val)
    {
        for (const auto& kp : *this) if (to_string(val) == to_string(*kp.second->getValue())) return true;
        return false;
    }
    template <typename T>
    void XAttributeMap<T>::RemoveWithValue(T val)
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

    template <typename T>
    XElementMap<T>::XElementMap(XElement* main_node) : node(main_node)
    {
        prefix = "";
        alt_name_func1 = [](std::string pref) { return new XName(pref); };
    }
    template <typename T>
    XElementMap<T>::XElementMap(XElement* main_node, std::string fpref, std::function<XName*(int)> func) : node(main_node)
    {
        prefix = fpref;
        name_func = func;
        alt_name_func1 = [](std::string pref) { return new XName(pref); };
    };
    template <typename T>
    void XElementMap<T>::AddElement(int key, std::string attr_pref, std::function<XAttribute*(int, T)> func)
    {
        if (!name_func) return;
        std::string t = prefix+std::to_string(key);
        if (this->count(t)) return;
        XElement* new_node = new XElement(name_func(key), 0);
        node->appendChild(new_node);
        (*this)[t] = new XAttributeMap<T>(new_node, attr_pref, func);
    };
    template <typename T>
    void XElementMap<T>::AddCustomElement(std::string key, std::string attr_pref, std::function<XAttribute*(int, T)> func)
    {
        std::string t = key;
        if (this->count(t)) return;
        XElement* new_node = new XElement(alt_name_func1(t), 0);
        node->appendChild(new_node);
        (*this)[t] = new XAttributeMap<T>(new_node, attr_pref, func);
    };
    template <typename T>
    void XElementMap<T>::AddCustomElement(XName* key, std::string attr_pref, std::function<XAttribute*(int, T)> func)
    {
        std::string t = key->xml();
        if (this->count(t)) return;
        XElement* new_node = new XElement(alt_name_func1(t), 0);
        node->appendChild(new_node);
        (*this)[t] = new XAttributeMap<T>(new_node, attr_pref, func);
    };
    template <typename T>
    void XElementMap<T>::AddCustomElement(int key, std::string ele_pref, std::string attr_pref, std::function<XAttribute*(int, T)> func)
    {
        std::string t = ele_pref+std::to_string(key);
        if (this->count(t)) return;
        XElement* new_node = new XElement(alt_name_func1(t), 0);
        node->appendChild(new_node);
        (*this)[t] = new XAttributeMap<T>(new_node, attr_pref, func);
    };
    template <typename T>
    XAttributeMap<T>* XElementMap<T>::operator()(int i)
    {
        return (*this)[prefix+to_string(i)];
    };
    template <typename T>
    XAttributeMap<T>* XElementMap<T>::operator()(int i, std::string ele_pref)
    {
        return (*this)[ele_pref+to_string(i)];
    };
    template <typename T>
    XAttributeMap<T>* XElementMap<T>::get(std::string ele_pref)
    {
        return (*this)[ele_pref];
    };
    template <typename T>
    XAttributeMap<T>* XElementMap<T>::get(XName* name)
    {
        return (*this)[name->xml()];
    };
    template <typename T>
    XAttribute* XElementMap<T>::operator()(int i, int j)
    {
        std::string attr_pref = (*this)[prefix+to_string(i)]->getPrefix();
        return (*(*this)[prefix+to_string(i)])[attr_pref+to_string(j)];
    };
    template <typename T>
    XAttribute* XElementMap<T>::operator()(int i, int j, std::string ele_pref, std::string attr_pref)
    {
        return (*(*this)[ele_pref+to_string(i)])[attr_pref+to_string(j)];
    };
    template <typename T>
    void XElementMap<T>::Clear()
    {
        this->clear();
        node->ClearChildren();
    }
    template <typename T>
    void XElementMap<T>::ClearAttributes()
    {
        for (auto it = this->begin(); it != this->end(); ++it)
        {
            it->second->Clear();
        }
    };
    template <typename T>
    void XElementMap<T>::ClearChildAttributes(XName* except = nullptr)
    {
        std::string comp = except == nullptr ? "" : except->getComparisonString();
        for (auto it = node->FirstChild(); it != node->LastChild(); ++it)
        {
            if ((*it)->getComparisonString() == comp) continue;
            (*it)->ClearAttributes();
        };
    }
}