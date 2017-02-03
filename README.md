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

Library will be installed in ```bash build/lib ```

Usage
-----
The directoy macro provide some usage example:
```bash
source setup.sh
root macro/test.C
```
