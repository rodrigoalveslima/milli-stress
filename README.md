# milli-stress
milli-stress has functions to stress computer systems for a short amount of
time and periodically generate transient resource contention in various physical
subsystems.

## CPU Stressor
The CPU stressor implements a Sieve of Erathostenes to check if a given number
is prime.

### Building
```
$ make
```

### Running
To check if `n` is prime every `interval` seconds for `duration` seconds or
`count` times:
```
$ ./milli-stress [n] [duration] [interval] [count]
```

If `duration = 0` and `count = 0`, the program runs indefinitely.

### Generating CPU millibottlenecks
The duration of CPU saturation is dependent on the hardware and the workload.
Intuitively, a CPU with higher clock rate should run the algorithm for a certain
number `n` faster than another CPU with lower clock rate, given that other
specifications like cache size are the same, producing a briefer saturation
(i.e., a shorter bottleneck).

In the following running example, we show how to generate CPU millibottlenecks
for a specific hardware configuration.

#### Running Example
The following experiment was run on a C8220 machine with two 10-core Intel Ivy
Bridge CPUs at 2.20 GHz running Ubuntu 18.04 LTS 64 bits.
```
Architecture:        x86_64
CPU op-mode(s):      32-bit, 64-bit
Byte Order:          Little Endian
CPU(s):              40
On-line CPU(s) list: 0-39
Thread(s) per core:  2
Core(s) per socket:  10
Socket(s):           2
NUMA node(s):        2
Vendor ID:           GenuineIntel
CPU family:          6
Model:               62
Model name:          Intel(R) Xeon(R) CPU E5-2660 v2 @ 2.20GHz
Stepping:            4
CPU MHz:             2201.770
CPU max MHz:         2200.0000
CPU min MHz:         1200.0000
BogoMIPS:            4400.21
Virtualization:      VT-x
L1d cache:           32K
L1i cache:           32K
L2 cache:            256K
L3 cache:            25600K
```

The machine was hosted on CloudLab and an identical setup can be instantiated
with the public CloudLab profile `Infosphere/C8220-Ubuntu18.04LTS64bit`.

To simplify the analysis, disable hyper-threading and all but one CPU core. For
a C8220 machine with 40 virtual cores (`cpu0`, `cpu1`, ..., `cpu39`):
```
$ sudo su
# for i in {1..39}; do echo "0" > /sys/devices/system/cpu/cpu$i/online; done
# exit
```

Run `lscpu` and check that only `cpu0` is on-line:
```
...
On-line CPU(s) list:  0
Off-line CPU(s) list: 1-39
...
```

For more reproducible results, disable any dynamic overclocking feature like
Intel TurboBoost. For the `intel_pstate` power scaling driver used in modern
Intel CPUs:
```
$ sudo su
# echo 1 > /sys/devices/system/cpu/intel_pstate/no_turbo
# exit
```

Also, install the `cpupower` utility and activate the `performance` frequency
governor so the CPU runs at maximum frequency all the time. For Ubuntu 18.04
(Linux 4.0.15):
```
$ sudo apt-get update
$ sudo apt-get install linux-tools-common linux-tools-4.15.0-101-generic
$ sudo cpupower frequency-set -g performance
```

Run `cpupower frequency-info` and check that `cpu0` is running at maximum
frequency (2.20 GHz for a C8220 machine):
```
analyzing CPU 0:
  driver: intel_pstate
  CPUs which run at the same hardware frequency: 0
  CPUs which need to have their frequency coordinated by software: 0
  maximum transition latency:  Cannot determine or is not supported.
  hardware limits: 1.20 GHz - 2.20 GHz
  available cpufreq governors: performance powersave
  current policy: frequency should be within 1.20 GHz and 2.20 GHz.
                  The governor "performance" may decide which speed to use
                  within this range.
  current CPU frequency: Unable to call hardware
  current CPU frequency: 2.20 GHz (asserted by call to kernel)
  boost state support:
    Supported: no
    Active: no
    25500 MHz max turbo 4 active cores
    25500 MHz max turbo 3 active cores
    25500 MHz max turbo 2 active cores
    25500 MHz max turbo 1 active cores
```

To monitor CPU utilization, install Collectl:
```
$ sudo apt-get update
$ sudo apt-get install collectl
```
