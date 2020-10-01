# milli-stress
milli-stress has functions to stress computer systems for a short amount of
time and generate transient resource contention in various physical subsystems.

## CPU Stressor
The CPU stressor implements a Sieve of Erathostenes to check if a given number
is prime.

### Build
```
make
```

### Running
To check if `n` is prime every `interval` seconds for `duration` seconds or
`count` times:
```
./milli-stress [n] [duration] [interval] [count]
```

If `duration = 0` and `count = 0`, the program runs indefinitely.
