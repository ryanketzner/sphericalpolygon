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

## Reproducing Results from the Article

`mars_tests.sh` reproduces results from the Mars polygon test cases (Figures 18 and 19 in the article).

`comparison_tests.sh` reproduces the results from the Tennessee, radiometer, and square sensor test cases (Tables 3 and 4, Figures 13-15).

`memory_tests_no_preprocessing.sh` and `memory_tests.sh` reproduce the results from the memory consumption test case (Figure 16 in the article).

`crossing_tests.sh` reproduces the results from the edge crossing tests in the article (Table 1).

## Notes on CGAL Spherical Polygon Package

An attempt was made to validate this software against the CGAL package 5.4.1, "2D Boolean Operations on Nef Polygons Embedded on the Sphere," which provides functionality for operations on spherical polygons including contruction, exploration, and point location. We were unable to produce correct results in some basic test cases using the CGAL code; for instance, the CGAL code incorrectly evaluates the centroid of the TN polygon used as a test case in the article to be outside of its boundary. Since the CGAL package doesn't provide extensive documentation of its point location functions, we were unable to diagnose the issue further, but we have included the code here in case it is of interest to CGAL experts.

This test is available in the `cgal` directory, in the source file `cgal/NefPolygons.cpp`. The code takes the path to an input polygon and runs the CGAL point location algorithm on its centroid and antipode. It also will print some basic information about the polygon which is produced from utilies available in the CGAL package.

The CGAL example can be built using the accompanying CMakeFile. The CGAL library is a dependency for this example, and must be installed prior to build. The executable can be run on any of the polygons in the `examples/testpolygons` folder using the command:

`./NefPolygons <path_to_polygon_file>`

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

* GMAT2020a `gmatutil` source (https://sourceforge.net/p/gmat/git/ci/GMAT-R2020a/tree/src/gmatutil/)

## Questions?

Please contact Ryan Ketzner (ketzner@ucf.edu)
