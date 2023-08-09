#!/bin/bash
echo "Setting up..."
ln -s OpenBitKlavier.lua ~/Library/Application\ Support/REAPER/Scripts/OpenBitKlavier.lua
mkdir ~/Documents/bitSamples
mkdir ~/Documents/bitSamples/XSynth
./code/render setup
python3 test_arduino.py