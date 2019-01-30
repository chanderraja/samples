Class LinearAlgebraLib::Matrix<T, M, N>
========================================
A C++ template class representing a MxN matrix with integral or floating point members. 
The member type is specified by the template parameter T. This class is not thread safe.
Currently, the only matrix operations implemented are matrix multiplication and transposition.
A unit test application is provided as source code in the file test.cpp. A CMakeLists.txt file is provided
to allow building the unit test using cmake. 

Class Usage examples
--------------------
All examples below assume that the following declaration is used.

    using namespace LinearAlgebraLib;

#### Initialization

    Matrix<float, 2, 2> m1 = { 0.1f, -0.2f, -0.3f, 0.4f };
    Matrix<uint8_t, 2, 4> m2({1, 4, 6, 10, 2, 7, 5, 3});
    Matrix<int, 4, 3> m3({1, 4, 6, -2, 7, 5, 9, 0, -11, 3, 1, 0});

####  Multiplication

    Matrix<int, 2, 4> m1({1, 4, 6, 10, 2, 7, 5, 3});
    Matrix<int, 4, 3> m2({1, 4, 6, 2, 7, 5, 9, 0, 11, 3, 1, 0});
    
    auto *prod = m1 * m2;
   

In the above example, `prod` is a pointer to a newly allocated matrix of type `Matrix<int, 2, 3>`
and it is the user's responsibility to delete it appropriately when no longer needed.

Note that multiplication is only supported for matrix operands with compatible row and column combinations.

For example, the following code snippet will result in a compiler error:

    Matrix<int, 2, 4> m1({1, 4, 6, 10, 2, 7, 5, 3});
    Matrix<int, 3, 3> m2({1, 4, 6, 2, 7, 5, 9, 0, 11});
    
    auto *prod = m1 * m2;

####  Transposition

    Matrix<int, 2, 4> m({1, 4, 6, 10, 2, 7, 5, 3});

    Matrix<int, 4, 2> *mt = m.transpose();

How to build the unit test
--------------------------
To build and run the included GoogleTest based unit tests:
	
	> cmake .
	> make
	> ./matrix_test
	
NOTE: GoogleTest requires cmake 3.0 or greater. On a system like Centos 7,
which has an older version installed, cmake might return an error. In that case,
please upgrade to cmake 3.x and try again.

On a Centos 7 system, for example, you may have to do the following:
    
    > sudo yum install cmake3
    > cmake3 .
    > make
    > ./matrix_test
    
How to generate the class documentation
---------------------------------------
To generate HTML documentation for the Matrix class and methods:

    > doxygen
