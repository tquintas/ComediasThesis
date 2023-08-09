#!/bin/bash
echo "Starting..."
osascript open_reaper_bitklavier.applescript
./code/render start
python3 port_listener.py