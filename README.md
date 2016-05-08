# timeside
Timing side channel attack binary


To build on Ubuntu:
```
gcc timeside.c -o timeside -lcrypto
```

To built on Windows using MingGW:
```
gcc -Imingw32/include timeside.c -o timeside -Lmingw32/lib -lcrypto -lssl
```

