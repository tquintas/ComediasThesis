# 17 Comédias
## Master's thesis on musical composition (not completed)
This currently works in macOS Ventura 13.2.1, with an Apple M1 Chip.

I'm Tiago Quintas and this is the repository containing all the code and sheet music necessary to run/play my piece _17 Comédias_.

---

### Dependencies
For this piece to work, you'll need:
1. The latest version of [Reaper](https://www.reaper.fm) and [bitKlavier](https://bitklavier.com).
2. The latest version of [Python3](https://www.python.org), including the packages ``serial``, ``re``, and ``subprocess``. If you don't have those packages, you'll need to run: ``pip3 install <package_name>``.
3. The latest version of [Arduino IDE](https://www.arduino.cc/en/software) (and a Arduino UNO with the components shown below).
4. The Reaper's packages/APIs [ultraschall](https://ultraschall.fm/api/) and [Lokasenna GUI](https://jalovatt.github.io/scythe/#/) using ReaPack.

---

### Getting started
Firstly, to use the contents of this repository, you have to clone the repository to a custom folder, connect the Arduino to the computer and hit the reset button, and create all the folders and aliases needed. You can do that running the commands:

    cd <custom_folder>
    git clone https://github.com/tquintas/ComediasThesis.git
    cd ComediasThesis
    ./setup.sh

That shell command will create an alias of the ``OpenBitKlavier.lua`` file in Reaper's resource pack folder, will create folders for the samples for bitKlavier and will test the connection for Arduino. If the console prints ``Connection success!`` then everything is fine! If not, make sure everything is connected properly and check which port the Arduino is connected to. Usually the port is ``/dev/cu.usbmodem[number]``. Copy that path and on the ``port_listener.py`` file, and paste it on the variable in line 4.

Then, head to the Reaper application, go to ```Actions >> Show action list... >> New action... >> Load ReaScript...``` and then select the ``OpenBitKlavier.lua`` file. After that, click on the new action created and add the shortcut ``Cmd+Opt+Shift+O``. Now, if you press that shortcut, a little window will appear with all the options needed for the piece. Click on the ``FX Setup`` button. A message box will appear and follow those steps to create presets on the bitKlavier plugin. Close Reaper.

Now you're good to start playing!

---

### Play the piece
To start playing, first check if your keyboard os connected to the the mixer by MIDI and that your audio output is set correctly. Then, open the file ``rendering.ino`` and upload the code to your Arduino, after connecting all the components to it. Each module is constructed like the image of the file ``arduino.key``, with a total of 5 models. Then, open the terminal, navigate to your repo folder and run:

    ./start.sh

This will open Reaper, load all the plugins and stablish a serial connection between the Arduino and the python code that renders new samples and new bitKlavier's galleries.

You can, then, start playing! Good luck! :D

## Task list!

- [x] Finish the GitHub repository.
- [ ] Create the header files.
- [ ] Re-read the state of art.
- [ ] Complete the xml.cpp file.
- [ ] Make a file for every interlude, with the types of random sounds and random patches.
- [ ] Make a file for every piece, with the correct patches and sounds.