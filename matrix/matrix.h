///
/// \file
/// Implementation of a templatized matrix class
///
/// \author Chander Raja
///

#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <cmath>
#include <array>
#include <iostream>
#include <algorithm>
#include <type_traits>


namespace LinearAlgebraLib {

/// \class Matrix<T,M,N>
///
/// \brief A template class representing a MxN matrix whose member elements can be integral or floating point.
/// Note that the methods of this class are not thread safe.
///
/// \tparam T matrix data type (int, float, double etc)
/// \tparam M number of rows in matrix
/// \tparam N number of columns in matrix
template<typename T, size_t M, size_t N>
class Matrix {

    std::array<std::array<T, N>, M> *m_matrix;
    std::array<std::array<T, N>, M>& m_elem;

public:

    /// \brief default constructor. Elements are zeroed out during initialization
    Matrix()
        : m_matrix(new std::array<std::array<T, N>, M>({}))
        , m_elem(*m_matrix)
        {}

    /// \brief constructor with array initializer -  example usage: Matrix<int, 2, 2> m{ 1, 2, -3, -4 };
    /// \param initializer 2D array with values to initialize matrix from
    explicit  Matrix(const std::array<std::array<T, N>, M>& initializer)
        : m_matrix(new std::array<std::array<T, N>, M>(initializer))
        , m_elem(*m_matrix)
    {
    }

    ~Matrix()
    {
        delete m_matrix;
    }

    /// \brief assignment operator - example usage: Matrix<int, 2, 2> m = { 1, 2, -3, -4 };
    /// \param initializer
    /// \return reference to this matrix
    Matrix& operator=(const std::array<std::array<T, M>, N>& initializer) { m_elem = initializer;  return *this; }

    /// \return the number of rows in the matrix
    size_t rows() const { return M; }

    /// \return the number of columns in the matrix
    size_t columns() const { return N; }

    /// \brief non-const index operator overload for write access to matrix elements - usage is m[{row, column}] = value;
    /// \param a pair of row and column indices into the matrix. if indices are out of bounds,
    /// an out of bound exception is thrown
    /// \return a non-const reference to an element in the matrix
    /// \throws std::out_of_range if either index is out of range
    T& operator[] (const std::pair<size_t, size_t>& a)
    {
        return m_elem.at(a.first).at(a.second); // use at() instead of [] because it throws out of bound exception
    }

    /// \brief const index operator overload for read only access to matrix elements- usage is m[{row, column}]
    /// \param a pair of row and column indices into the matrix. if indices are out of bounds,
    /// an out of bound exception is thrown
    /// \return a const reference to an element in the matrix
    /// \throws std::out_of_range if either index is out of range
    const T& operator[] (const std::pair<size_t, size_t>& a) const
    {
        return m_elem.at(a.first).at(a.second); // use at() instead of [] because it throws out of bound exception
    }

    /// \brief equal-to comparison operator overload for integral types
    /// \param b other matrix to compare with
    /// \return true if equal to other matrix, false otherwise
    template<typename U = T>
    typename std::enable_if<std::is_integral<U>::value, bool>::type operator==(const Matrix& b) const
    {
        return (m_elem == b.m_elem);
    }

    /// \brief equal-to comparison operator overload for floating point types
    /// \param b other matrix to compare with
    /// \return true if equal to other matrix, false otherwise
    template<typename U = T>
    typename std::enable_if<std::is_floating_point<U>::value, bool>::type operator==(const Matrix& b) const
    {
        for (size_t row = 0; row < M; ++row) {
            for (size_t col = 0; col < N; ++col) {
                T x = m_elem[row][col];
                T y = b.m_elem[row][col];
                T epsilon_factor = std::fmax(std::fabs(x), std::fabs(y));
                bool almost_equal = (std::fabs(x - y) <= std::numeric_limits<T>::epsilon()*epsilon_factor);
                if (!almost_equal) return false;
            }
        }

        return true;
    }

    /// \brief not-equal-to comparison operator
    /// \param b other matrix to compare with
    /// \return true if not equal to other matrix, false otherwise
    bool operator!=(const Matrix& b) const { return !(*this==b); }


    /// \brief This method perform matrix multiplication with a NxL matrix. The result will be a newly allocated
    /// MxN matrix containing the product of the matrix multiplication
    /// \tparam L number of columns in other operand matrix and product matrix
    /// \param b second operand in the matrix multiplication
    /// \return pointer to a newly allocated MxL matrix containing the product of this matrix and b
    template<size_t L>
    Matrix<T, M, L>* operator*(const Matrix<T, N, L>& b)
    {
        auto* prod = new Matrix<T, M, L>;

        for (size_t row = 0; row < M; ++row) {
            for (size_t col = 0; col < L; ++col) {
                for (size_t i = 0; i < N; ++i) {
                    (*prod)[{row, col}] += (m_elem[row][i] * b[{i, col}]);
                 }
            }
        }

        return prod;

    }


    /// \brief This method returns a NxM matrix that is the transpose of this matrix
    /// \return pointer to a newly allocated NxM matrix containing the transpose data from this matrix
    Matrix<T, N, M>* transpose()
    {
        auto* transposed = new Matrix<T, N, M>;

        for (size_t row = 0; row < M; ++row) {
            for (size_t col = 0; col < N; ++col) {
                (*transposed)[{col, row}] = m_elem[row][col];
            }
        }

        return transposed;
    }


};



/// \brief Overloading of operator<< to dump the matrix contents to an output stream
/// \tparam T matrix element value type
/// \tparam M number of matrix rows
/// \tparam N number of matrix columns
/// \param os reference to output steam
/// \param m MxN matrix containing elements of type T
/// \return
template<typename T, size_t M, size_t N>
std::ostream& operator<<(std::ostream& os, const Matrix<T, M, N>& m)
{
    for (size_t row = 0; row < M; ++row) {
        for (size_t col = 0; col < N; ++col) {
            os << m[{row, col}] << "\t";
        }
        os << std::endl;
    }
    return os;
}

} // namespace LinearAlgebraLib

#endif //__MATRIX_H__
