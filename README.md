# extlib
Personal library with some handy utilities

## building
```
make
make extlib.pc
make install
```

## using
simply include `extlib.h`

to use `malloc_secure` and `free_secure` `USE_SECURE_MEM` has to be defined.

to use `rrmdir` `_XOPEN_SOURCE` has to be defined as `500`
