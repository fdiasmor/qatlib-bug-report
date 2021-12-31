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
#### 1) Install the `qatlib` at `~/QAT/build` as recommended in the instructions (default behavior).
```
export ICP_ROOT=$HOME/QAT
./configure
sudo make -j
sudo make install
```
#### 2) Go to samples_code and compile the fips library.
```
$ cd quickassist/lookaside/access_layer/src/sample_code
$ export ICP_ROOT=$HOME/QAT
$ make fips_code
```

Verify that the `fips_sample_s.so` has been created.

```
$ ls fips/build/linux_2.6/user_space/
cpa_fips_sample_aes_gcm.o  cpa_fips_sample_dsa.o  cpa_fips_sample_ecdsa.o  cpa_fips_sample_rsa.o  cpa_fips_sample_utils.o  fips_sample.a  fips_sample_s.so
```

#### 3) Download and compile a test example that links to fips_sample_s.so.
 
```
$ cd fips
$ git clone https://github.com/fdiasmor/qatlib-bug-report.git
$ cp -r qatlib-bug-report/issue0/* .
$ cmake -S . -B test-build
$ cmake --build test-build
```

Refer to the output show in the beginning of this text to see the error.

#### Some explanation 

The error `fips_sample_s.so: undefined reference to 'cpaCyNrbgGetEntropy'` can fixed by introducing `${ICP_LAC_DIR}/src/common/crypto/sym/nrbg/lac_sym_nrbg_api.c` to the compilation, where `ICP_LAC_DIR = ${ICP_ROOT}/quickassist/lookaside/access_layer`. This fix can be reproduced by `issue1` in `https://github.com/fdiasmor/qatlib-bug-report.git` -- see below.

```
$ export ICP_ROOT=$HOME/QAT
$ git clone https://github.com/fdiasmor/qatlib-bug-report.git
$ cd qatlib-bug-report/issue1
$ cmake -S . -B build
$ cmake --build build
```

Note that only the error `fips_sample_s.so: undefined reference to `generateRandomBytes'` remains. 

```
$ cmake --build build
Scanning dependencies of target domodexp
[ 10%] Building C object test2/CMakeFiles/domodexp.dir/domodexp.c.o
[ 20%] Building C object test2/CMakeFiles/domodexp.dir/cpa_fips_sample_rsa.c.o
[ 30%] Building C object test2/CMakeFiles/domodexp.dir/home/fdiasmor/workspace/QAT/quickassist/lookaside/access_layer/src/common/crypto/sym/nrbg/lac_sym_nrbg_api.c.o
[ 40%] Building C object test2/CMakeFiles/domodexp.dir/cpa_fips_sample_utils.c.o
[ 50%] Building C object test2/CMakeFiles/domodexp.dir/cpa_fips_sample_aes_gcm.c.o
[ 60%] Building C object test2/CMakeFiles/domodexp.dir/cpa_fips_sample_dsa.c.o
[ 70%] Building C object test2/CMakeFiles/domodexp.dir/cpa_fips_sample_ecdsa.c.o
[ 80%] Linking C shared library libdomodexp.so
[ 80%] Built target domodexp
Scanning dependencies of target modexp
[ 90%] Building CXX object test2/CMakeFiles/modexp.dir/main.cpp.o
[100%] Linking CXX executable modexp
libdomodexp.so: undefined reference to `generateRandomBytes'
collect2: error: ld returned 1 exit status
gmake[2]: *** [test2/modexp] Error 1
gmake[1]: *** [test2/CMakeFiles/modexp.dir/all] Error 2
gmake: *** [all] Error 2

```

The error `fips_sample_s.so: undefined reference to `generateRandomBytes'` happens because CPM_LACKS_DRBG is defined -- as per the original compilation. Other compilation errors appear when CPM_LACKS_DRBG is not defined. 
