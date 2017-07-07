![Snapshot](https://github.com/eminfedar/easyprograminstaller/raw/master/snap1.jpg)
# Easy Program Installer (EPI)
EPI is a program for installing most used programs by users easily after a fresh boot of a new os.
It has been written in C++ & Qt-5, so you can compile the program yourself if you have Qt-Creator.

# How to install EPI?
### You can download .deb file from here: (Easy & Fast)
* [Download .deb file](https://github.com/eminfedar/easyprograminstaller/releases/download/v1.4.2/easyprograminstaller_1.4.2_amd64.deb)
* And install: `sudo dpkg -i easyprograminstaller_1.4.2_amd64.deb`
* Then run it: `easyprograminstaller`


### Or if you are a developer you can compile from source code:

1. Compile [yaml-cpp](https://github.com/jbeder/yaml-cpp) _(Recommended 0.5.1)_:
```
git clone --branch release-0.5.1 --single-branch https://github.com/jbeder/yaml-cpp
cd yaml-cpp
mkdir build
cd build

cmake ..
make
sudo make install
```
2. Do not forget to copy 'yaml-cpp-clonedfolderfromgithub/include/yaml-cpp' folder to project folder (same with .pro and .cpp's path)
3. Open ".pro" file with QT-Creator

Done.
