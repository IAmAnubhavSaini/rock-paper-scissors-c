# rock-paper-scissors-c

You know the older and boring version of rock-paper-scissors-lizard-spock.

## build

```bash
gcc -Wall -Wextra -Wpedantic -Wshadow -Wconversion -g -o rps.exe rock-paper-scissors.c


./rps.exe

Your choices are: 1.Rock 2.Paper 3.Scissors.
Please press appropriate digit: 2

You chose: Paper
Computer chose: Scissors
Scissors wins.%

./rps.exe

Your choices are: 1.Rock 2.Paper 3.Scissors.
Please press appropriate digit: 1

You chose: Rock
Computer chose: Scissors
Rock wins.%
```

## A walk through C data structure

```c
void initiate_randomness(void)
{
    srand(time(NULL));
}
```

#error message read:

```text
In file included from rock-paper-scissors.c:7:
random_integers.c: In function ‘initiate_randomness’:
random_integers.c:6:11: warning: conversion from ‘time_t’ {aka ‘long int’} to ‘unsigned int’ may change value [-Wconversion]
    6 |     srand(time(NULL));
      |
```

`time()` comes from `time.h`:

```c
#ifndef __USE_TIME_BITS64
/* Return the current time and put it in *TIMER if TIMER is not NULL.  */
extern time_t time (time_t *__timer) __THROW;
```

`time_t` comes from `time_t.h`

```c
/* Returned by `time'.  */
#ifdef __USE_TIME_BITS64
typedef __time64_t time_t;
#else
typedef __time_t time_t;
#endif
```

`__time_t` comes from `types.h`

```c
__STD_TYPE __TIME_T_TYPE __time_t;	/* Seconds since the Epoch.  */

// somewhere in the same file:
/* No need to mark the typedef with __extension__.   */
# define __STD_TYPE		typedef
```

`__TIME_T_TYPE` comes from `typesizes.h`

```c
#define __TIME_T_TYPE		__SYSCALL_SLONG_TYPE
```

`__SYSCALL_SLONG_TYPE` comes from `typesizes.h` (same file)

```c
/* X32 kernel interface is 64-bit.  */
#if defined __x86_64__ && defined __ILP32__
# define __SYSCALL_SLONG_TYPE	__SQUAD_TYPE
# define __SYSCALL_ULONG_TYPE	__UQUAD_TYPE
#else
# define __SYSCALL_SLONG_TYPE	__SLONGWORD_TYPE
# define __SYSCALL_ULONG_TYPE	__ULONGWORD_TYPE
#endif
```

We are interested in `# define __SYSCALL_SLONG_TYPE	__SLONGWORD_TYPE`.

And from `types.h` we get `__SLONGWORD_TYPE`

```c
#define __SLONGWORD_TYPE	long int
```

So `time()` returns `long int`.

What's happening?

`time()` returns `long int`. `srand()` accepts `unsigned int`. `long int` is bigger than `unsigned int`, that means, it can actually truncate or wrap the value around. As the behavior is implementation defined.

So, mere casting won't work. I need to mod the value. And that causes another randomness-seed related problem, but one problem at a time.

Thus the fix becomes:

```c
#include <limits.h>

void initiate_randomness(void)
{
    time_t t = time(NULL);
    srand(t % UINT_MAX);
}
```

Actually, it doesn't, still gotta typecast.

```c
#include <limits.h>

void initiate_randomness(void)
{
    time_t t = time(NULL);
    srand((unsigned int)(t % (time_t)UINT_MAX));
}
```

## License

The MIT License (MIT)

Copyright (c) 2013-2025 Anubhav Saini
