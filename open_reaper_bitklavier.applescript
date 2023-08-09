tell application "REAPER"
	activate
end tell

delay 8

tell application "System Events"
	tell application process "REAPER"
		try
			click button "Still Evaluating" of window 1
		end try
		keystroke "o" using (command down & option down & shift down)
		delay 0.5
		set reload to window "Reloading..."
		delay 0.2
		key down {command}
		key down "0"
		delay 0.02
		key up "0"
		key up {command}
	end tell
end tell
