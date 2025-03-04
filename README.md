# Neutron attenuation in TPP2MnBr4 and PP:ZnS

This is simulation code for neutron attenuation in metal halide hybrids. As a particle source spectrum from SINQ was used.

To build code run:

```sh
source geant4.sh # depends on shell and system
mkdir build
cd build
cmake ..
make -jN # N is number of cores, example: make -j5
```

To run simulation(here you need to run commands under build folder):

```sh
./neutrons -m macro.mac -p physList_name -u UIsession -t nThreadss # if you do not need some flags - do not specify them
```

Simple example of usage with default UI session and 10 threads:

```sh
./neutrons -t 10
```

Examples of analysis code:

```sh
python3 -m venv env
pip install -r requirements.txt
source env/bin/activate # depends on shell
python3 analysis.py
```
Script `analysis.py` can be modified to your needs
