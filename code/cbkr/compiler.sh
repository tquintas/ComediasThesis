#!/bin/bash

echo "Compiling..."
files=("wav" "qsynth" "serialMatrix" "xml" "xnode" "xtext" "xname" "xattribute" "xelement" "xmaps" "xdocument" "xpreparation" "xpiano" "xkeymap" "xdirect" "xsynchronic" "xnostalgic" "xtempo" "xtuning" "xblendronic" "xresonance" "xreset" "xcomment" "xgeneral" "bitklavier")

for file in "${files[@]}"
do
    echo "Compiling $file.cpp..."
    g++-12 -fdiagnostics-color=always -g -c "$file.cpp" -o "$file.o"
done

add_ext() {
    local items=("$@")
    for item in "${items[@]}"
    do
        echo "$item.o"
    done
}
echo "Linking..."
files_ext=($(add_ext "${files[@]}"))
libtool -static -o libbitKlavier.a "${files_ext[@]}" -L/usr/local/lib -lfftw3
sudo cp libbitKlavier.a /usr/local/lib
echo "Complete!"