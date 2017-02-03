# WA105_LightSoft

Process and reconstruct light signal from the WA105 3x1x1 prototype

Download
--------
```bash
git clone https://github.com/remotain/WA105_LightSoft.git
```
Install
-------
```bash
mkdir build && cd build
cmake ../
make
```
The package depends only on [ROOT](http://root.cern.ch/).

Libraries are located in ```build/lib ```

Usage
-----
To setup the framework's environment:
```bash
source setup.sh
```
Run the macros available in the ```macro```directory:
```bash
root macro/test.C
```
