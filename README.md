# WA105_LightSoft

Process and reconstruct light signal from the WA105 3x1x1 prototype

Download
--------
```bash
git clone https://github.com/remotain/WA105_LightSoft.git
```
Install
-------
The package depends only on [ROOT](http://root.cern.ch/) v5-34-34. The compatibility with more recent versions (ROOOT-6) is not granted. 

Make sure your ```$ROOTSYS``` variable is set and pointing to a valid ROOT installation.

```bash
cd WA105_LightSoft/
mkdir build && cd build
cmake ../ 
make 
cd ../
```
Libraries are located in ```WA105_LightSoft/build/lib ```

Usage
-----
To setup the framework's environment:
```bash
source setup.sh
```
Run the macros available in the ```macro```directory:
```bash
root macro/simple_ana.C"(run_number)"
```
