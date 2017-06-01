![Snapshot](https://github.com/eminfedar/easyprograminstaller/raw/master/snap1.jpg)
# Easy Program Installer (EPI)
EPI is a program for installing most used programs by users easily after a fresh boot of a new os.
It has been written in C++ & Qt-5, so you can compile the program yourself if you have Qt-Creator.

# How to install EPI?
### You can download .deb file from here: (Easy & Fast)
* [Download .deb file](https://github.com/eminfedar/easyprograminstaller/releases/download/v1.1/easyprograminstaller_1.1_amd64.deb)
* And install: `sudo dpkg -i easyprograminstaller_1.1_amd64.deb`
* Then run it from terminal : `easyprograminstaller`

### You can compile from source code:
It needs some policy file to run without asking sudo password.
You must copy those 2 file to the those locations:
```
org.fedar.easyprograminstaller.policy -> /usr/share/polkit-1/actions
org.fedar.easyprograminstaller.rules  -> /usr/share/polkit-1/rules.d
```
And do not forget to copy the program file to `/usr/bin` folder.
Otherwise it will require sudo password.
