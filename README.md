# Point in Spherical Polygon Algorithm Implementation

This repository contains the software implementation of the algorithm described in the article, "A Robust, Fast and Accurate Algorithm for Point in Spherical Polygon with Applications in Geoscience and Remote Sensing." The main items of interest in this repository are three scripts in the root directory `comparison_tests.sh`, `mars_tests.sh`, and `tennessee_tests.sh`. Once the code is compiled, these scripts can be run to reproduce the results (runtime measurements, algorithm output) demonstrated in the article on the target system. 

## Directory Structure
```
├── build
├── exe
├── lib
│   ├── extern
│   │   └── gmatutil
│   │       ├── base
│   │       ├── include
│   │       └── util
│   │           ├── interpolator
│   │           └── matrixoperations
│   └── lib
│       └── propcov-cpp
├── src
│   └── main
├── testpolygons
│   ├── Mars
│   └── Tennessee
├── testqueries
└── tests
    ├── build
    └── src
```

Object files and dependency files used in the compilation process are written to the `build` directory.

The executable files for the point in spherical polygon routine (PIP.exe) and the GMAT reference routine (GMATmain.exe) are generated in the `exe` directory.

`lib` contains external dependencies. These include `gmatutil`, from NASA's GMAT2020a software, and `propcov-cpp`, from EOSim.

`src` contains the source code for the point in spherical polygon routine implementation.

`testpolygons` contains .csv input files for the polygons tested in the article.

`testqueries` contains .csv query point input files used for the tests in the article.

`tests` contains unit tests which were used to verify basic functionality during the software development process. These are not present in the article but should help to verify that the software is working correctly.

## Install

Requires: Unix-like operating system, GNU build tools (gcc, make). Google's unittest library is a dependency for the unit tests. The unit tests are not necessary to run the software. 

1. Navigate to the `lib/extern` directory and run `make`. 
2. Navigate to the `lib/lib` directory and run `make`.
3. Run `make` from the repo root directory.
4. Execute `make runtest` to run unit tests and verify basic functionality (optional). All tests should read "PASSED".

## License and Copyright

Copyright 2021 Bay Area Environmental Research Institute

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

## Credits and Acknowledgments

This work has been funded by grants from the National Aeronautics and Space Administration (NASA) Earth Science Technology Office (ESTO) through the Advanced Information Systems Technology (AIST) Program.

External libraries used:

> GMAT2020a `gmatutil` source (https://sourceforge.net/p/gmat/git/ci/GMAT-R2020a/tree/src/gmatutil/)
> Boost C++ libraries (https://www.boost.org/)
> JSON for Modern C++ (https://github.com/nlohmann/json)

## Questions?

Please contact Ryan Ketzner (rketzner@knights.ucf.edu)
