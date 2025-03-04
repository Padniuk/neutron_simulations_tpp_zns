# Neutron attenuation in TPP $_2$ MnBr $_4$ and PP:ZnS

This is simulation code for neutron attenuation in metal halide hybrids. As a particle source spectrum from SINQ was used.

To build code run:

```sh
mkdir build
cd build
cmake ..
make -jN # N is number of cores, example: make -j5
```

To run simulation(here you need to run commands under build folder):

```sh
./neutrons -m macro.mac -p physList_name -u UIsession -t nThreadss # if you do not need some flags - do not specify it
```

Simple example of usage with default UI session and 10 threads:

```sh
./neutrons -t 10
```