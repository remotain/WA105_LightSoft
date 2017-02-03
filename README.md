# WA105_LightSoft

Process and reconstruct light signal from the WA105 3x1x1 prototype

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
