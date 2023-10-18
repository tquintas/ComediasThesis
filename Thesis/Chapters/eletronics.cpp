#include "bitklavier.hpp"

using namespace bkr;

int main(int argc, char* argv[])
{
    int complexity = 800;
    BitKlavier* bk = new BitKlavier(XAttribute::bitKlavierAttributes.Name("TestGallery"));
    XDirect* direct = bk->CreateDirect();
    XKeymap* keymap = bk->CreateKeymap();
    direct->RandomDirect(complexity);
    keymap->RandomKeymap(complexity);
    keymap->Connect(direct);
    bk->Save();
}