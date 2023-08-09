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
Firstly, to use the contents of this repository, you have to clone the repository to a custom folder, and then create an alias of the ``OpenBitKlavier.lua`` file inside the Scripts folder, on the Reaper's Resource Pack folder. You can follow those steps manually or writing in the terminal:

    cd <custom_folder>
    git clone https://github.com/tquintas/ComediasThesis.git
    cd <reaper_resource_pack/Scripts>
    ln -s <custom_folder/OpenBitKlavier.lua> OpenBitKlavier.lua

Then, head to the Reaper application, go to ```Actions >> Show action list... >> New action... >> Load ReaScript...``` and then select the ``OpenBitKlavier.lua`` file. After that, click on the new action created and add the shortcut ``Cmd+Opt+Shift+O``. Now, if you press that shortcut, a little window will appear with all the options needed for the piece.

To check if everything works correctly with the Arduino, you might need to change some bits in the code. Connect the Arduino to the computer and hit the reset button. Then, run the ``test_arduino.py`` file. If the console prints ``Connection success!`` then everything is fine! If not, make sure everything is connected properly and check which port the Arduino is connected to. Usually the port is ``/dev/cu.usbmodem[number]``. Copy that path and on the ``port_listener.py`` file, and paste it on the variable in line 4.
