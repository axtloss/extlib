# extlib
Personal library with some handy utilities

## building
Honestly, include this either as a git submodule or just the entire code tree (respect the license!!), and build it as part of your project instead of using it as a shared object, it makes things so much easier.

```
make
make extlib.pc
make install
```

## using
simply include `extlib.h`

to use `malloc_secure` and `free_secure` `USE_SECURE_MEM` has to be defined.

to use `rrmdir` `_XOPEN_SOURCE` has to be defined as `500`
