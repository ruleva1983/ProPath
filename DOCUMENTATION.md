# Authors

Dr. Ruggero Vasile (ruleva1983@gmail.com, ruggero.vasile@gfz-potsdam.de)

Dr. Enrico Ser Giacomi (enrico.sergiacomi@gmail.com)


# Overview

This under development library provides minimal ...

When using this code, please acknowledge the authors by citing [Ser-Giacomi et al. (2015a)](#references) and [Ser-Giacomi et al. (2015b)](#references). 



# Installation

To run all components of the library, tests and applications you need to install boost, gtest and Eigen libraries.


## Install boost (on Ubuntu)

For this project we need header only libraries of boost. To install:

* sudo apt-get install libboost-all-dev

This will install all header only boost libraries. In this project we are interested in the odeint library only.

## Install Gtest (on Ubuntu)

Gtest is used to compile and run the tests. Please refer to https://www.eriksmistad.no/getting-started-with-google-test-on-ubuntu/ for a proper installation on ubuntu system.

* sudo apt-get install libgtest-dev

* cd /usr/src/gtest

* sudo cmake CMakeLists.txt

* sudo make

* sudo cp *.a /usr/lib


## Install Eigen

Run the script

* install_eigen.sh


# Build

To build the all components just run the "build_from_scratch.sh" script. You will need cmake to be installed. If you make some changes and want to avoid to rebuild everything you can just run the "rebuild.sh" script. 

The executable files will be found within the build/ directory. Applications are in build/applications/name_of_application/

Description of each application can be found in each  application/name_of_application/ folder.



## References

[[Ser-Giacomi et al. 2015a]](https://journals.aps.org/pre/abstract/10.1103/PhysRevE.92.012818) Ser-Giacomi, E., Vasile, R., Hernández-García, E., & López, C. (2015). Most probable paths in temporal weighted networks: An application to ocean transport. *Physical review E*, 92(1), 012818.


[[Ser-Giacomi et al. 2015b]](https://aip.scitation.org/doi/abs/10.1063/1.4928704) Ser-Giacomi, E., Vasile, R., Recuerda, I., Hernández-García, E., & López, C. (2015). Dominant transport pathways in an atmospheric blocking event. *Chaos: an interdisciplinary journal of nonlinear science*, 25(8), 087413.
