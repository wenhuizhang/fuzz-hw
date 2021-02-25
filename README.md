# fuzz-hw
fuzz homework

```
In a new build folder, do the below for 5 rounds
CC=/usr/local/bin/afl-gcc CXX=/usr/local/bin/afl-g++ cmake ..
make
afl-fuzz -i ../testcases -o ../findings ./afldemo
rm -rf ./
```
