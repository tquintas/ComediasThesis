#include "xnode.hpp"

namespace bkr
{
    XNode::XNode() : offset(""), parent(nullptr) {};
    XNode::XNode(const XNode& other) : offset(other.offset), parent(nullptr)
    {
        if (other.parent != nullptr)
        {
            parent = new XNode;
            *parent = *(other.parent);
        }
    };
    XNode::~XNode() {};
    void XNode::setOffset(std::string off)
    {
        offset = off;
    };
    int XNode::getDepth(int i = 0)
    {
        if (parent == nullptr) return i;
        return parent->getDepth(i+1);
    };
    std::string XNode::getOffset()
    {
        offset = repeat("    ", getDepth());
        return offset;
    };
    void XNode::setParent(XNode* par)
    {
        parent = par;
    };
    XNode* XNode::getParent()
    {
        return parent;
    };
    bool XNode::operator==(XNode* other)
    {
        return getComparisonString() == other->getComparisonString();
    };
    std::string XNode::xml()
    {
        return "";
    };
    std::string XNode::getComparisonString()
    {
        return getOffset()+xml();
    };
    std::pair<bool, XNode*> XNode::has_descendant(XNode* xnode)
    {
        return std::make_pair(false, nullptr);
    };
    std::vector<XNode*> XNode::Descendants()
    {
        std::vector<XNode*> vect(0);
        return vect;
    };
    XNode* XNode::copy()
    {
        return new XNode(*this);
    };
    void XNode::ClearAttributes() {};
}