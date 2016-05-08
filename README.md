# timeside
Timing side channel attack binary

## Linux

Tested on Ubuntu.

To build:
```
gcc timeside.c -o timeside -lcrypto
```
To execute, ensure the ``timeside`` executable and the ``passfile.dat`` are in the same directory, then enter
```
timeside <pin>
```
Where <pin> is the number (up to 10 digits) you want to check.

## Windows

To build using MingGW:
```
gcc -Imingw32/include timeside.c -o timeside -Lmingw32/lib -lcrypto -lssl
```
To execute, ensure the ``timeside`` executable and the ``passfile.dat`` are in the same directory, then enter
```
timeside.exe <pin>
```
Where <pin> is the number (up to 10 digits) you want to check.


