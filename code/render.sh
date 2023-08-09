#!/usr/bin/osascript
on run argv
    set chn to item 1 of argv
    set comp to item 2 of argv
    do shell script "/Users/tiagoquintas/Documents/Finale/Silent\\ Piano/JS/cpp/render " & comp
    tell application "REAPER"
        activate
    end tell
    tell application "System Events"
        tell application process "REAPER"
            tell window "Reloading..."
                key down {command}
                key down chn
                delay 0.02
                key up chn
                key up {command}
            end tell
        end tell
    end tell
end run