```C
fd_set rfds;
struct timeval tv;
int retval;

FD_ZERO(&rfds);
FD_SET(0, &rfds);

tv.tv_sec = 5;
tv.tv_usec = 0;

retval = select(1, &rfds, NULL, NULL, &tv);
```

```C
#define __FDS_BITS(set) ((set)->__fds_bits)

#define __FD_ZERO(s) \
  do {									                                \
    unsigned int __i;							                        \
    fd_set *__arr = (s);						                        \
    for (__i = 0; __i < sizeof (fd_set) / sizeof (__fd_mask); ++__i)    \
      __FDS_BITS (__arr)[__i] = 0;					                    \
  } while (0)

#define __FD_SET(d, s) \
  ((void) (__FDS_BITS (s)[__FD_ELT(d)] |= __FD_MASK(d)))
```

```C
// FD_ZERO(&rfds);

do {					      
    unsigned int __i;					      
    fd_set *__arr = (&rfds);
    for (__i = 0; __i < sizeof (fd_set) / sizeof (__fd_mask); ++__i)
      ((__arr) -> __fds_bits)[__i] = 0;
  } while (0)


#define	__FD_ELT(d)	((d) / __NFDBITS)
#define	__FD_MASK(d)	((__fd_mask) (1UL << ((d) % __NFDBITS)))

// FD_SET(k, &rfds);

((void) (__FDS_BITS (&rfds)[__FD_ELT(k)] |= __FD_MASK(k)))

((void) (((&rfds) -> __fds_bits)[ ((k) / __NFDBITS) ] |= __FD_MASK(k)))

((void) ( ((&rfds) -> __fds_bits) [(k / 64)] |= __FD_MASK(k) ))

((void) ( ((&rfds) -> __fds_bits) [(k / 64)] |= ((__fd_mask) (1UL << (k % 64))) ))
// 1UL = 0...(63 zeros)...01
// 1UL << (k % 64) = 0...010...0 (1 на k-ом месте)
```