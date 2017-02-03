# WA105_LightSoft

Process and reconstruct light signal from the WA105 3x1x1 prototype

Download
--------
```bash
git clone https://github.com/remotain/WA105_LightSoft.git
```
Install
-------
The package depends only on [ROOT](http://root.cern.ch/) v5-34-34. The compatibility with other version is not granted. Make sure your ```$ROOTSYS``` variable is set and pointing to a valid root installation

```bash
cd WA105_LightSoft/
mkdir build && cd build
cmake ../
make
```
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
