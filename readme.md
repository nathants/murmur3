### three versions of the murmur3-x86-32, in java, python, and c.

- useful for hashing small inputs, like uuids, and is probably not the best choice for hashing large files

- identical implementations are handy for things such as sharing a consistent hashing scheme across languages

### java

```
>> cd java

>> javac Murmur3.java

>> java Murmur3 asdf
455139366
```

### python3

```
>> cd python

>> python3 setup.py install

>> python3 -c 'import murmur3; print(murmur3.hash("asdf"))'
455139366
```

### c

```
>> cd c

>> make

>> ./murmur3 asdf
455139366
```

### sources

java adapted from:
 - https://github.com/yonik/java_util/blob/94199ef60b7e12f57a3aa82fbbd5e2fa22726d8d/src/util/hash/MurmurHash3.java

c adapted from:
 - https://github.com/PeterScott/murmur3/tree/dae94be0c0f54a399d23ea6cbe54bca5a4e93ce4

python3 is the c code with a python3 wrapper from:
 - https://github.com/hajimes/mmh3/tree/361a373b578d885cd95b1d299b6b63a7c8894a5c

### license

All this code is in the public domain. Murmur3 was created by Austin Appleby. The above sources are ports by their respective authors and are in the public domain, as is everything else here.
