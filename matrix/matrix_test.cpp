//
// Created by Chander Raja on 2019-01-24.
//

// GoogleTest unittests for Matrix class
#include <iostream>
#include "matrix.h"
#include "gtest/gtest.h"

using namespace LinearAlgebraLib;
using namespace std;


namespace {

// To use a test fixture, derive a class from testing::Test.
class MatrixTest : public testing::Test {
protected:
    void SetUp() override {
    }
};


// Test default constructor
TEST_F(MatrixTest, TestDefaultConstructor)
{

    Matrix<int, 2, 2> mi;
    EXPECT_EQ(mi.rows(), 2);
    EXPECT_EQ(mi.columns(), 2);

    mi[{1, 1}] = -100;
    EXPECT_FLOAT_EQ((mi[{1, 1}]), -100);
    mi[{0, 1}] = 32768;
    EXPECT_FLOAT_EQ((mi[{0, 1}]), 32768);

    Matrix<float, 6, 6> mf;
    EXPECT_EQ(mf.rows(), 6);
    EXPECT_EQ(mf.columns(), 6);

    mf[{2, 2}] = 0.002345;
    EXPECT_FLOAT_EQ((mf[{2, 2}]), 0.002345);

    Matrix<double, 1920, 1080> mhd;
    EXPECT_EQ(mhd.rows(), 1920);
    EXPECT_EQ(mhd.columns(), 1080);

    mhd[{200, 200}] = 3.14159;
    EXPECT_DOUBLE_EQ((mhd[{200, 200}]), 3.14159);
 }

// Test constructor with array initializer
TEST_F(MatrixTest, TestConstructorWithArrayInitializer)
{

    Matrix<int, 2, 2> mi({0, 1, 1, 2});

    for (size_t row = 0; row < mi.rows(); ++row) {
        for (size_t col = 0; col < mi.columns(); ++col) {
            EXPECT_EQ((mi[{row,col}]), (row + col));
        }
    }
}


// Test assignment using array initializer
TEST_F(MatrixTest, TestAssignmentWithArrayInitializer)
{

    Matrix<int, 2, 2> mi;
    mi = {0, 1, 1, 2};

    for (size_t row = 0; row < mi.rows(); ++row) {
        for (size_t col = 0; col < mi.columns(); ++col) {
            EXPECT_EQ((mi[{row,col}]), (row + col));
        }
    }
}

// Test our of range indices
TEST_F(MatrixTest, TestOutOfRange)
{

    Matrix<double, 1920, 1080> mhd;

    bool outOfRangeException = false;

    try {
        double value = mhd[{1920, 1080}];
    }
    catch(std::out_of_range) {
        outOfRangeException = true;
    }
    EXPECT_TRUE(outOfRangeException);

    outOfRangeException = false;

    try {
        mhd[{1920, 1080}] = 10.0;
    }
    catch(std::out_of_range) {
        outOfRangeException = true;
    }

    EXPECT_TRUE(outOfRangeException);
}

// Test multiplication
TEST_F(MatrixTest, TestMultiply)
{

    // Test floating point matrix multiplication
    Matrix<float, 2, 2> mf1({0.1f, 0.2f, 0.3f, 0.4f});
    Matrix<float, 2, 2> mf2({1.f, 2.f, 3.f, 4.f});

    Matrix<float, 2, 2> mf_expected({0.7f, 1.0f, 1.5f, 2.2f});

    auto * mf_prod = mf1 * mf2;

    EXPECT_EQ(mf_prod->rows(), 2);
    EXPECT_EQ(mf_prod->columns(), 2);
    EXPECT_EQ(*mf_prod, mf_expected);

    delete mf_prod;

    // Test unsigned long integer matrix multiplication
    Matrix<unsigned long, 2, 4> mul1({1, 4, 6, 10, 2, 7, 5, 3});
    Matrix<unsigned long, 4, 3> mul2({1, 4, 6, 2, 7, 5, 9, 0, 11, 3, 1, 0});
    Matrix<unsigned long, 2, 3> mul_expected({93, 42, 92, 70, 60, 102});

    auto * mul_prod = mul1 * mul2;

    EXPECT_EQ(mul_prod->rows(), 2);
    EXPECT_EQ(mul_prod->columns(), 3);
    EXPECT_EQ(*mul_prod, mul_expected);

    delete mul_prod;

}

// Test transposition
TEST_F(MatrixTest, TestTranspose) {

    Matrix<unsigned long, 2, 4> mul({1, 4, 6, 10, 2, 7, 5, 3});
    Matrix<unsigned long, 4, 2> mul_expected({1, 2, 4, 7, 6, 5, 10, 3});

    auto * mul_transposed = mul.transpose();

    EXPECT_EQ(mul_transposed->rows(), 4);
    EXPECT_EQ(mul_transposed->columns(), 2);
    EXPECT_EQ(*mul_transposed, mul_expected);

    Matrix<int, 1, 4> mi({1, -4, 6, -10});
    Matrix<int, 4, 1> mi_expected({1, -4, 6, -10});

    auto * mi_transposed = mi.transpose();

    EXPECT_EQ(mi_transposed->rows(), 4);
    EXPECT_EQ(mi_transposed->columns(), 1);
    EXPECT_EQ(*mi_transposed, mi_expected);


    }

} // namespace