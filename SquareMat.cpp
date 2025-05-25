//agassinoa20@gmail.com
#include "SquareMat.hpp"
#include <cmath>
#include <iostream>

namespace matrix {

/// @brief Constructor that initializes a size x size matrix with zeros
SquareMat::SquareMat(int size) : size(size), matrix(nullptr) {
    if (size <= 0) {
        throw MatrixException("matrix size must be positive");
    }
    matrix = new double[size * size];
    for (int i = 0; i < size * size; ++i) {
        matrix[i] = 0.0;
    }
}

/// @brief Constructor that initializes a matrix with provided values
SquareMat::SquareMat(int size, const double* initData) : size(size), matrix(nullptr) {
    if (size <= 0) {
        throw MatrixException("matrix size must be positive");
    }
    matrix = new double[size * size];
    for (int i = 0; i < size * size; ++i) {
        matrix[i] = initData[i];
    }
}

/// @brief Copy constructor that performs deep copy
SquareMat::SquareMat(const SquareMat& other) : size(other.size), matrix(new double[other.size * other.size]) {
    copyMem(other);
}

/// @brief Assignment operator that handles self-assignment and deep copy
SquareMat& SquareMat::operator=(const SquareMat& other) {
    if (this != &other) {
        if (this->size != other.size) {
            delete[] matrix;
            size = other.size;
            matrix = new double[size * size];
        }
        copyMem(other);
    }
    return *this;
}

/// @brief Destructor to free matrix memory
SquareMat::~SquareMat() {
    delete[] matrix;
}

/// @brief Helper to copy matrix contents
void SquareMat::copyMem(const SquareMat& other) {
    for (int i = 0; i < size * size; ++i) {
        matrix[i] = other.matrix[i];
    }
}
// Non-const index access operator: returns a proxy Row object.
SquareMat::Row SquareMat::operator[](int row) {
    if (row < 0 || row >= size) {
        throw MatrixException("Row index out of bounds");
    }
    return Row(matrix + row * size);
}

// Const index access operator: returns a proxy ConstRow object.
SquareMat::ConstRow SquareMat::operator[](int row) const {
    if (row < 0 || row >= size) {
        throw MatrixException("Row index out of bounds");
    }
    return ConstRow(matrix + row * size);
}

// Implementation of Row's operator[]
double& SquareMat::Row::operator[](int col) {
    if (col < 0) {
        throw MatrixException("Column index cannot be negative");
    }
    // Note: We assume the caller knows the matrix dimensions;
    return rowData[col];
}

// Implementation of ConstRow's operator[]
const double& SquareMat::ConstRow::operator[](int col) const {
    if (col < 0) {
        throw MatrixException("Column index cannot be negative");
    }
    return rowData[col];
}
/// @brief Element-wise addition assignment
SquareMat& SquareMat::operator+=(const SquareMat& rhs) {
    if (size != rhs.size) {
        throw MatrixException("Matrices must have the same dimensions for +=");
    }
    for (int i = 0; i < size * size; ++i) {
        matrix[i] += rhs.matrix[i];
    }
    return *this;
}

/// @brief Element-wise subtraction assignment
SquareMat& SquareMat::operator-=(const SquareMat& rhs) {
    if (size != rhs.size) {
        throw MatrixException("Matrices must have the same dimensions for -=");
    }
    for (int i = 0; i < size * size; ++i) {
        matrix[i] -= rhs.matrix[i];
    }
    return *this;
}

/// @brief Standard matrix multiplication assignment
SquareMat& SquareMat::operator*=(const SquareMat& rhs) {
    if (size != rhs.size) {
        throw MatrixException("Matrices must have the same dimensions for multiplication");
    }
    SquareMat result(size);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            double sum = 0.0;
            for (int k = 0; k < size; ++k) {
                sum += matrix[i * size + k] * rhs.matrix[k * size + j];
            }
            result.matrix[i * size + j] = sum;
        }
    }
    *this = result;
    return *this;
}

/// @brief Scalar multiplication assignment
SquareMat& SquareMat::operator*=(double scalar) {
    for (int i = 0; i < size * size; ++i) {
        matrix[i] *= scalar;
    }
    return *this;
}

/// @brief Scalar division assignment
SquareMat& SquareMat::operator/=(double scalar) {
    if (scalar == 0.0) {
        throw MatrixException("Division by zero");
    }
    for (int i = 0; i < size * size; ++i) {
        matrix[i] /= scalar;
    }
    return *this;
}

/// @brief Element-wise multiplication assignment
SquareMat& SquareMat::operator%=(const SquareMat& rhs) {
    if (size != rhs.size) {
        throw MatrixException("Matrices must have the same dimensions for element-wise multiplication");
    }
    for (int i = 0; i < size * size; ++i) {
        matrix[i] *= rhs.matrix[i];
    }
    return *this;
}

/// @brief Scalar modulo assignment
SquareMat& SquareMat::operator%=(int mod) {
    if (mod == 0) {
        throw MatrixException("Modulo by zero is undefined");
    }
    for (int i = 0; i < size * size; ++i) {
        matrix[i] = std::fmod(matrix[i], static_cast<double>(mod));
    }
    return *this;
}

/// @brief Prefix increment: increases all elements by 1
SquareMat& SquareMat::operator++() {
    for (int i = 0; i < size * size; ++i) {
        ++matrix[i];
    }
    return *this;
}

/// @brief Postfix increment: returns original matrix before increment
SquareMat SquareMat::operator++(int) {
    SquareMat temp(*this);
    ++(*this);
    return temp;
}

/// @brief Prefix decrement: decreases all elements by 1
SquareMat& SquareMat::operator--() {
    for (int i = 0; i < size * size; ++i) {
        --matrix[i];
    }
    return *this;
}

/// @brief Postfix decrement: returns original matrix before decrement
SquareMat SquareMat::operator--(int) {
    SquareMat temp(*this);
    --(*this);
    return temp;
}

/// @brief Unary minus: returns new matrix with all elements negated
SquareMat SquareMat::operator-() const {
    SquareMat result(size);
    for (int i = 0; i < size * size; ++i) {
        result.matrix[i] = -matrix[i];
    }
    return result;
}

/// @brief Transpose of the matrix
SquareMat SquareMat::operator~() const {
    SquareMat result(size);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            result.matrix[j * size + i] = matrix[i * size + j];
        }
    }
    return result;
}
double SquareMat::operator!() const {
    if (size == 0) {
        throw MatrixException("Determinant undefined for 0x0 matrix.");}

    if (size == 1) {
        return matrix[0];}

    if (size == 2) {
        return matrix[0] * matrix[3] - matrix[1] * matrix[2]; }

    double detVal = 0.0;
    for (int col = 0; col < size; ++col) {
        int reducedSize = size - 1;
        double* tempData = new double[reducedSize * reducedSize];
        int index = 0;

        for (int i = 1; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (j == col) continue;
                tempData[index++] = matrix[i * size + j];
            }
        }
        SquareMat minor(reducedSize, tempData);
        delete[] tempData;

        double sign = (col % 2 == 0) ? 1.0 : -1.0;
        detVal += sign * matrix[col] * (!minor);
    }

    return detVal;
}


/// @brief Power operation using binary exponentiation
SquareMat SquareMat::operator^(int power) const {
    if (power < 0) {
        throw MatrixException("Negative powers not supported");
    }
    SquareMat result = SquareMat::identity(size);
    SquareMat base(*this);
    while (power > 0) {
        if (power % 2 == 1) {
            result *= base;
        }
        base *= base;
        power /= 2;
    }
    return result;
}

/// @brief Equality comparison based on matrix sum
bool SquareMat::operator==(const SquareMat& other) const {
    return sum() == other.sum();
}

/// @brief Inequality comparison based on matrix sum
bool SquareMat::operator!=(const SquareMat& other) const {
    return !(*this == other);
}

/// @brief Less than comparison based on matrix sum
bool SquareMat::operator<(const SquareMat& other) const {
    return sum() < other.sum();
}

/// @brief Greater than comparison based on matrix sum
bool SquareMat::operator>(const SquareMat& other) const {
    return sum() > other.sum();
}

/// @brief Less than or equal comparison based on matrix sum
bool SquareMat::operator<=(const SquareMat& other) const {
    return sum() <= other.sum();
}

/// @brief Greater than or equal comparison based on matrix sum
bool SquareMat::operator>=(const SquareMat& other) const {
    return sum() >= other.sum();
}

/// @brief Output stream operator
std::ostream& operator<<(std::ostream& os, const SquareMat& mat) {
    for (int i = 0; i < mat.size; ++i) {
        for (int j = 0; j < mat.size; ++j) {
            os << mat.matrix[i * mat.size + j] << " ";
        }
        os << '\n';
    }
    return os;
}

/// @brief Creates an identity matrix of given size
SquareMat SquareMat::identity(int n) {
    SquareMat id(n);
    for (int i = 0; i < n; ++i) {
        id.matrix[i * n + i] = 1.0;
    }
    return id;
}

/// @brief Sums all elements in the matrix
double SquareMat::sum() const {
    double total = 0.0;
    for (int i = 0; i < size * size; ++i) {
        total += matrix[i];
    }
    return total;
}

/// @brief Returns the matrix size
int SquareMat::getSize() const {
    return size;
}

/// @brief External operator+: lhs + rhs
SquareMat operator+(const SquareMat& lhs, const SquareMat& rhs) {
    return SquareMat(lhs) += rhs;
}

/// @brief External operator-: lhs - rhs
SquareMat operator-(const SquareMat& lhs, const SquareMat& rhs) {
    return SquareMat(lhs) -= rhs;
}

/// @brief External operator*: lhs * rhs (matrix multiplication)
SquareMat operator*(const SquareMat& lhs, const SquareMat& rhs) {
    return SquareMat(lhs) *= rhs;
}

/// @brief External operator*: matrix * scalar
SquareMat operator*(const SquareMat& mat, double scalar) {
    return SquareMat(mat) *= scalar;
}

/// @brief External operator*: scalar * matrix
SquareMat operator*(double scalar, const SquareMat& mat) {
    return mat * scalar;
}

/// @brief External operator/: matrix / scalar
SquareMat operator/(const SquareMat& mat, double scalar) {
    return SquareMat(mat) /= scalar;
}

/// @brief External operator%: lhs % rhs (element-wise multiplication)
SquareMat operator%(const SquareMat& lhs, const SquareMat& rhs) {
    return SquareMat(lhs) %= rhs;
}

/// @brief External operator%: matrix % scalar
SquareMat operator%(const SquareMat& mat, int mod) {
    return SquareMat(mat) %= mod;
}

} // namespace matrix
