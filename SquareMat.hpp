agassinoa20@gmail.com
#ifndef SQUARMAT_HPP
#define SQUARMAT_HPP

#include <iostream>

namespace matrix {

class SquareMat {
private:
    int size;
    double* matrix;

    void copyMem(const SquareMat& other);

public:
    // Constructor and Destructor
    SquareMat(int n);
    SquareMat(int size, const double* initData);
    SquareMat(const SquareMat& other);
    SquareMat& operator=(const SquareMat& other);
    ~SquareMat();

    // Unary and indexing
    SquareMat operator-() const;
    SquareMat& operator++();
    SquareMat operator++(int);
    SquareMat& operator--();
    SquareMat operator--(int);
    SquareMat operator~() const;
    double operator!() const;
    SquareMat operator^(int power) const;

    // Equality and comparisons
    bool operator==(const SquareMat& other) const;
    bool operator!=(const SquareMat& other) const;
    bool operator<(const SquareMat& other) const;
    bool operator>(const SquareMat& other) const;
    bool operator<=(const SquareMat& other) const;
    bool operator>=(const SquareMat& other) const;

    // Compound assignment
    SquareMat& operator+=(const SquareMat& rhs);
    SquareMat& operator-=(const SquareMat& rhs);
    SquareMat& operator*=(const SquareMat& rhs);
    SquareMat& operator*=(double scalar);
    SquareMat& operator/=(double scalar);
    SquareMat& operator%=(const SquareMat& rhs);
    SquareMat& operator%=(int mod);

    class Row {
        private:
            double* rowData;
        public:
            explicit Row(double* data) : rowData(data) {}
            double& operator[](int col);  // Provide modifiable access (bounds checking in implementation)
        };

    class ConstRow {
        private:
            const double* rowData;
        public:
            explicit ConstRow(const double* data) : rowData(data) {}
            const double& operator[](int col) const;
        };

    // Non-const access.
    Row operator[](int row);
    // Const access.
    ConstRow operator[](int row) const;


    friend std::ostream& operator<<(std::ostream& os, const SquareMat& mat);
    static SquareMat identity(int n);
    double sum() const;
    int getSize()const;
};

// Binary operators (defined outside the class)
SquareMat operator+(const SquareMat& lhs, const SquareMat& rhs);
SquareMat operator-(const SquareMat& lhs, const SquareMat& rhs);
SquareMat operator*(const SquareMat& lhs, const SquareMat& rhs);
SquareMat operator*(const SquareMat& mat, double scalar);
SquareMat operator*(double scalar, const SquareMat& mat);
SquareMat operator/(const SquareMat& mat, double scalar);
SquareMat operator%(const SquareMat& lhs, const SquareMat& rhs);
SquareMat operator%(const SquareMat& mat, int mod);

} // namespace matrix

#endif // SQUARMAT_HPP
