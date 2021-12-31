#  Issue Output
```
$ cmake -S . -B build
-- The C compiler identification is GNU 4.8.5
-- The CXX compiler identification is GNU 4.8.5
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: /usr/bin/cc - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done
-- Generating done
-- Build files have been written to: /home/fdiasmor/QAT/quickassist/lookaside/access_layer/src/sample_code/fips/build
$ cmake --build build
Scanning dependencies of target test
[ 50%] Building CXX object test/CMakeFiles/test.dir/main.cpp.o
[100%] Linking CXX executable test
../../test/../build/linux_2.6/user_space/fips_sample_s.so: undefined reference to `cpaCyNrbgGetEntropy'
../../test/../build/linux_2.6/user_space/fips_sample_s.so: undefined reference to `generateRandomBytes'
collect2: error: ld returned 1 exit status
gmake[2]: *** [test/test] Error 1
gmake[1]: *** [test/CMakeFiles/test.dir/all] Error 2
gmake: *** [all] Error 2
```
## How to Reproduce Issue
### Assumptions

These instructions assume that you are working with the version give by the tarball `QAT.L.4.15.0-00011.tar.gz`, which was downloaded from https://01.org/intel-quick-assist-technology. 

Note that the latest version was recently changed to L.4.16.0-00017. Another assumption is that these versions are fairly the same for the purpose of reproducing this issue.

Proceed with the following to prepare for the `qatlib` compilation.

```
$ cd ~
$ mkdir QAT
$ mv QAT.L.4.15.0-00011.tar.gz QAT/
$ cd QAT
$ tar zxvf QAT.L.4.15.0-00011.tar.gz
```
### Steps 

1) Install the `qatlib` at `~/QAT/build` as recommended in the instructions.
```
export ICP_ROOT=~/QAT
./configure
make -j
sudo make install
```
2) Go to samples_code and compile the fips library.
```
$ cd quickassist/lookaside/access_layer/src/sample_code
$ cd fips
```
3) Create and compile a test example that attempts to use functions defined in fips_sample_s.so.
 
